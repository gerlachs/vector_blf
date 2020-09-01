/*
 * Copyright (C) 2013-2020 Tobias Lorenz.
 * Contact: tobias.lorenz@gmx.net
 *
 * This file is part of Tobias Lorenz's Toolkit.
 *
 * Commercial License Usage
 * Licensees holding valid commercial licenses may use this file in
 * accordance with the commercial license agreement provided with the
 * Software or, alternatively, in accordance with the terms contained in
 * a written agreement between you and Tobias Lorenz.
 *
 * GNU General Public License 3.0 Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl.html.
 */

#include <Vector/BLF/FileStatistics.h>

#include <string>

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/Exceptions.h>

namespace Vector {
namespace BLF {

void FileStatistics::read(AbstractFile & is) {
    is.read(reinterpret_cast<char *>(&signature), sizeof(signature));
    if (signature != FileSignature)
        throw Exception("FileStatistics::read(): File signature doesn't match at this position.");
    is.read(reinterpret_cast<char *>(&statisticsSize), sizeof(statisticsSize));
    is.read(reinterpret_cast<char *>(&unknown1), sizeof(unknown1));
    is.read(reinterpret_cast<char *>(&unknown2), sizeof(unknown2));
    is.read(reinterpret_cast<char *>(&unknown3), sizeof(unknown3));
    is.read(reinterpret_cast<char *>(&unknown4), sizeof(unknown4));
    is.read(reinterpret_cast<char *>(&applicationId), sizeof(applicationId));
    is.read(reinterpret_cast<char *>(&objectsRead), sizeof(objectsRead));
    is.read(reinterpret_cast<char *>(&applicationMajor), sizeof(applicationMajor));
    is.read(reinterpret_cast<char *>(&applicationMinor), sizeof(applicationMinor));
    is.read(reinterpret_cast<char *>(&fileSize), sizeof(fileSize));
    is.read(reinterpret_cast<char *>(&uncompressedFileSize), sizeof(uncompressedFileSize));
    is.read(reinterpret_cast<char *>(&objectCount), sizeof(objectCount));
    is.read(reinterpret_cast<char *>(&applicationBuild), sizeof(applicationBuild));
    is.read(reinterpret_cast<char *>(&measurementStartTime), sizeof(measurementStartTime));
    is.read(reinterpret_cast<char *>(&lastObjectTime), sizeof(lastObjectTime));
    is.read(reinterpret_cast<char *>(&fileSizeWithoutUnknown115), sizeof(fileSizeWithoutUnknown115));
    is.read(reinterpret_cast<char *>(reservedFileStatistics.data()), static_cast<std::streamsize>(reservedFileStatistics.size() * sizeof(uint32_t)));
}

void FileStatistics::write(AbstractFile & os) {
    os.write(reinterpret_cast<char *>(&signature), sizeof(signature));
    os.write(reinterpret_cast<char *>(&statisticsSize), sizeof(statisticsSize));
    os.write(reinterpret_cast<char *>(&unknown1), sizeof(unknown1));
    os.write(reinterpret_cast<char *>(&unknown2), sizeof(unknown2));
    os.write(reinterpret_cast<char *>(&unknown3), sizeof(unknown3));
    os.write(reinterpret_cast<char *>(&unknown4), sizeof(unknown4));
    os.write(reinterpret_cast<char *>(&applicationId), sizeof(applicationId));
    os.write(reinterpret_cast<char *>(&objectsRead), sizeof(objectsRead));
    os.write(reinterpret_cast<char *>(&applicationMajor), sizeof(applicationMajor));
    os.write(reinterpret_cast<char *>(&applicationMinor), sizeof(applicationMinor));
    os.write(reinterpret_cast<char *>(&fileSize), sizeof(fileSize));
    os.write(reinterpret_cast<char *>(&uncompressedFileSize), sizeof(uncompressedFileSize));
    os.write(reinterpret_cast<char *>(&objectCount), sizeof(objectCount));
    os.write(reinterpret_cast<char *>(&applicationBuild), sizeof(applicationBuild));
    os.write(reinterpret_cast<char *>(&measurementStartTime), sizeof(measurementStartTime));
    os.write(reinterpret_cast<char *>(&lastObjectTime), sizeof(lastObjectTime));
    os.write(reinterpret_cast<char *>(&fileSizeWithoutUnknown115), sizeof(fileSizeWithoutUnknown115));
    os.write(reinterpret_cast<char *>(reservedFileStatistics.data()), static_cast<std::streamsize>(reservedFileStatistics.size() * sizeof(uint32_t)));
}

uint32_t FileStatistics::calculateStatisticsSize() const {
    return
        sizeof(signature) +
        sizeof(statisticsSize) +
        sizeof(unknown1) +
        sizeof(unknown2) +
        sizeof(unknown3) +
        sizeof(unknown4) +
        sizeof(applicationId) +
        sizeof(objectsRead) +
        sizeof(applicationMajor) +
        sizeof(applicationMinor) +
        sizeof(fileSize) +
        sizeof(uncompressedFileSize) +
        sizeof(objectCount) +
        sizeof(applicationBuild) +
        sizeof(measurementStartTime) +
        sizeof(lastObjectTime) +
        sizeof(fileSizeWithoutUnknown115) +
        static_cast<uint32_t>(reservedFileStatistics.size() * sizeof(uint32_t));
}

}
}
