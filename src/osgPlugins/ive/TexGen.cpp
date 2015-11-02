﻿/**********************************************************************
 *
 *    FILE:            TexGen.cpp
 *
 *    DESCRIPTION:    Read/Write osg::TexGen in binary format to disk.
 *
 *    CREATED BY:        Auto generated by iveGenerated
 *                    and later modified by Rune Schmidt Jensen.
 *
 *    HISTORY:        Created 21.3.2003
 *
 *    Copyright 2003 VR-C
 **********************************************************************/

#include "Exception.h"
#include "TexGen.h"
#include "Object.h"

using namespace ive;

void TexGen::write(DataOutputStream* out){
    // Write TexGen's identification.
    out->writeInt(IVETEXGEN);
    // If the osg class is inherited by any other class we should also write this to file.
    osg::Object*  obj = dynamic_cast<osg::Object*>(this);
    if(obj){
        ((ive::Object*)(obj))->write(out);
    }
    else
        out_THROW_EXCEPTION("TexGen::write(): Could not cast this osg::TexGen to an osg::Object.");
    // Write TexGen's properties.

    // Write mode
    out->writeInt(getMode());

    if ( out->getVersion() >= VERSION_0005 )
    {
        out->writePlane(getPlane(osg::TexGen::S));
        out->writePlane(getPlane(osg::TexGen::T));
        out->writePlane(getPlane(osg::TexGen::R));
        out->writePlane(getPlane(osg::TexGen::Q));
    }
}

void TexGen::read(DataInputStream* in){
    // Peek on TexGen's identification.
    int id = in->peekInt();
    if(id == IVETEXGEN){
        // Read TexGen's identification.
        id = in->readInt();
        // If the osg class is inherited by any other class we should also read this from file.
        osg::Object*  obj = dynamic_cast<osg::Object*>(this);
        if(obj){
            ((ive::Object*)(obj))->read(in);
        }
        else
            in_THROW_EXCEPTION("TexGen::read(): Could not cast this osg::TexGen to an osg::Object.");
        // Read TexGen's properties
        setMode((osg::TexGen::Mode)in->readInt());

        if ( in->getVersion() >= VERSION_0005 )
        {
            setPlane(osg::TexGen::S, in->readPlane());
            setPlane(osg::TexGen::T, in->readPlane());
            setPlane(osg::TexGen::R, in->readPlane());
            setPlane(osg::TexGen::Q, in->readPlane());
        }

    }
    else{
        in_THROW_EXCEPTION("TexGen::read(): Expected TexGen identification.");
    }
}
