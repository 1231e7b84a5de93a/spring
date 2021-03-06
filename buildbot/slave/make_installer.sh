#!/bin/bash
set -e
. buildbot/slave/prepare.sh


DEST=${TMP_BASE}/inst
#FIXME: remove hardcoded /usr/local
INSTALLDIR=${DEST}/usr/local

echo "Installing into $DEST"

#Ultra settings, max number of threads taken from commandline.
SEVENZIP="7z a -t7z -m0=lzma -mx=9 -mfb=64 -md=32m -ms=on -mmt=${2:-on}"
ZIP="zip -r9"

MINGWLIBS_PATH=${1}
MINGW_HOST=i586-mingw32msvc-

cd ${BUILDDIR}
make install DESTDIR=${DEST}

#strip symbols and archive them
cd ${INSTALLDIR}
EXECUTABLES="spring.exe spring-dedicated.exe spring-multithreaded.exe spring-headless.exe unitsync.dll ArchiveMover.exe springserver.dll $(find AI/Skirmish -name SkirmishAI.dll) $(find AI/Interfaces -name AIInterface.dll)"
for tostripfile in ${EXECUTABLES}; do
	if [ -f ${tostripfile} ]; then
		# dont strip binaries that we processed earlier
		if ! ${MINGW_HOST}objdump -h ${tostripfile} | grep -q .gnu_debuglink; then
			echo "stripping ${tostripfile}"
			debugfile=${tostripfile%.*}.dbg
			${MINGW_HOST}objcopy --only-keep-debug ${tostripfile} ${debugfile}
			${MINGW_HOST}strip --strip-debug --strip-unneeded ${tostripfile}
			${MINGW_HOST}objcopy --add-gnu-debuglink=${debugfile} ${tostripfile}
		else
			echo "not stripping ${tostripfile}"
		fi
	fi
done

mkdir -p ${TMP_PATH}

#absolute path to the minimal portable (engine, unitsync + ais)
MIN_PORTABLE_ARCHIVE=${TMP_PATH}/spring_${VERSION}_minimal-portable.7z
MIN_PORTABLE_PLUS_DEDICATED_ARCHIVE=${TMP_PATH}/spring_${VERSION}_minimal-portable+dedicated.zip

#create portable spring excluding shard (ask AF why its excluded)
touch ${INSTALLDIR}/springsettings.cfg
${SEVENZIP} ${MIN_PORTABLE_ARCHIVE} ${INSTALLDIR}/* -x!spring-dedicated.exe -x!spring-headless.exe -x!ArchiveMover.exe -xr!*.dbg -x!AI/Skirmish/Shard
#for ZKL
(cd ${INSTALLDIR} && ${ZIP} ${MIN_PORTABLE_PLUS_DEDICATED_ARCHIVE} * -x spring-headless.exe ArchiveMover.exe \*.dbg AI/Skirmish/Shard/\*)

# compress files excluded from portable archive
for file in spring-dedicated.exe spring-headless.exe ArchiveMover.exe; do
	name=${file%.*}
	${SEVENZIP} ${TMP_PATH}/${VERSION}_${name}.7z ${file}
done

#compress shard
${SEVENZIP} ${TMP_PATH}/${VERSION}_Shard.7z AI/Skirmish/Shard -xr!*.dbg

#create archives for translate_stacktrace.py
for tocompress in ${EXECUTABLES}; do
	#get parent-parent-directory name of file
	name=$(basename $(dirname $(dirname ${tocompress})))

	#set to filename without suffix if no parent dir
	if [ ${name} == "." ]; then
		name=${tocompress%.*}
	fi
	debugfile=${tocompress%.*}.dbg
	archive_debug="${TMP_PATH}/${VERSION}_${name}_dbg.7z"
	[ ! -f ${debugfile} ] || ${SEVENZIP} "${archive_debug}" ${debugfile}
done

cd ${SOURCEDIR}

# create symlinks required for building installer
rm -f ${SOURCEDIR}/installer/downloads/spring_testing_minimal-portable.7z
mkdir -p ${SOURCEDIR}/installer/downloads/
ln -sv ${MIN_PORTABLE_ARCHIVE} ${SOURCEDIR}/installer/downloads/spring_testing_minimal-portable.7z

rm -f  ${SOURCEDIR}/installer/downloads/ArchiveMover_testing.7z
ln -sv ${TMP_PATH}/${VERSION}_ArchiveMover.7z ${SOURCEDIR}/installer/downloads/ArchiveMover_testing.7z

# create installer
./installer/make_installer.sh

# move installer to rsync-directory
mv ./installer/spring*.exe ${TMP_PATH}

# create relative symbolic links to current files for rsyncing
cd ${TMP_PATH}/..
ln -sfv ${REV}/*.exe spring_testing.exe
ln -sfv ${REV}/spring_${VERSION}_minimal-portable.7z spring_testing_minimal-portable.7z
ln -sfv ${REV}/spring_${VERSION}_minimal-portable+dedicated.zip spring_testing_minimal-portable+dedicated.zip
ln -sfv ${REV}/${VERSION}_ArchiveMover.7z ArchiveMover_testing.7z

# create a file which contains the latest version of a branch
echo ${VERSION} > LATEST

