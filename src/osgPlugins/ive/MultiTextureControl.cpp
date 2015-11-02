﻿/**********************************************************************
 *
 *    FILE:            MultiTextureControl.cpp
 *
 *    DESCRIPTION:    Read/Write osg::MultiTextureControl in binary format to disk.
 *
 *    CREATED BY:        Auto generated by iveGenerate
 *                    and later modified by Rune Schmidt Jensen.
 *
 *    HISTORY:        Created 24.3.2003
 *
 *    Copyright 2003 VR-C
 **********************************************************************/

#include "Exception.h"
#include "MultiTextureControl.h"
#include "Group.h"

using namespace ive;

void MultiTextureControl::write(DataOutputStream* out){
    // Write MultiTextureControl's identification.
    out->writeInt(IVEMULTITEXTURECONTROL);
    // If the osg class is inherited by any other class we should also write this to file.
    osg::Group*  group = dynamic_cast<osg::Group*>(this);
    if(group){
        ((ive::Group*)(group))->write(out);
    }
    else
        out_THROW_EXCEPTION("MultiTextureControl::write(): Could not cast this osg::MultiTextureControl to an osg::Group.");
    // Write MultiTextureControl's properties.


    // Write rangelist
    unsigned int size = getNumTextureWeights();
    out->writeUInt(size);
    for(unsigned int i=0;i<size;i++)
    {
        out->writeFloat(getTextureWeight(i));
    }
}

void MultiTextureControl::read(DataInputStream* in){
    // Peek on MultiTextureControl's identification.
    int id = in->peekInt();
    if(id == IVEMULTITEXTURECONTROL){
        // Read MultiTextureControl's identification.
        id = in->readInt();

        // If the osg class is inherited by any other class we should also read this from file.
        osg::Group*  group = dynamic_cast<osg::Group*>(this);
        if(group){
            ((ive::Group*)(group))->read(in);
        }
        else
            in_THROW_EXCEPTION("MultiTextureControl::read(): Could not cast this osg::MultiTextureControl to an osg::Group.");
        // Read MultiTextureControl's properties


        // Read rangelist
        unsigned int size = in->readUInt();
        for(unsigned int i=0;i<size;i++)
        {
            float value = in->readFloat();
            setTextureWeight(i, value);
        }
    }
    else{
        in_THROW_EXCEPTION("MultiTextureControl::read(): Expected MultiTextureControl identification.");
    }
}
