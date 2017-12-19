/*
 * Copyright (C) 2013 Tobias Lorenz.
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

#include <Vector/BLF/SingleByteSerialEvent.h>

namespace Vector {
namespace BLF {


SingleByteSerialEvent::SingleByteSerialEvent() :
    byte()
{
}

SingleByteSerialEvent::~SingleByteSerialEvent()
{
}

void SingleByteSerialEvent::read(AbstractFile & is)
{
    is.read(reinterpret_cast<char *>(&byte), sizeof(byte));
}

void SingleByteSerialEvent::write(AbstractFile & os)
{
    os.write(reinterpret_cast<char *>(&byte), sizeof(byte));
}

DWORD SingleByteSerialEvent::calculateObjectSize() const
{
    return sizeof(byte);
}

}
}