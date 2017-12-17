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

#pragma once

#include <Vector/BLF/platform.h>

#include <array>

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/ObjectHeader.h>
#include <Vector/BLF/VectorTypes.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief FLEXRAY_SYNC
 *
 * @deprecated
 */
class VECTOR_BLF_EXPORT FlexRaySync final : public ObjectHeader
{
public:
    FlexRaySync();

    virtual void read(AbstractFile & is) override;
    virtual void write(AbstractFile & os) override;
    virtual DWORD calculateObjectSize() const override;

    /**
     * @brief application channel
     */
    WORD channel;

    /** multiplexer */
    BYTE mux;

    /** length */
    BYTE len;

    /** message id */
    WORD messageId;

    /** CRC */
    WORD crc;

    /** direction */
    BYTE dir;

    /** reserved */
    BYTE reservedFlexRaySync1;

    /** reserved */
    WORD reservedFlexRaySync2;

    /** data bytes */
    std::array<BYTE, 11> dataBytes;

    /** cycle */
    BYTE cycle;
};

}
}
