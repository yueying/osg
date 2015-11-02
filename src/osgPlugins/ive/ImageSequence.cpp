﻿/**********************************************************************
 *
 *    FILE:            Image.cpp
 *
 *    DESCRIPTION:    Read/Write osg::Image in binary format to disk.
 *
 *    CREATED BY:        Auto generated by iveGenerated
 *                    and later modified by Rune Schmidt Jensen.
 *
 *    HISTORY:        Created 20.3.2003
 *
 *    Copyright 2003 VR-C
 **********************************************************************/

#include "Exception.h"
#include "ImageSequence.h"
#include "Object.h"

#include <osg/Notify>
#include <osgDB/Options>

using namespace ive;

void ImageSequence::write(DataOutputStream* out)
{
    // Write ImageSequence's identification.
    out->writeInt(IVEIMAGESEQUENCE);
    // If the osg class is inherited by any other class we should also write this to file.
    osg::Object*  obj = dynamic_cast<osg::Object*>(this);
    if(obj){
        ((ive::Object*)(obj))->write(out);
    }
    else
        out_THROW_EXCEPTION("ImageSequence::write(): Could not cast this osg::ImageSequence to an osg::Object.");
    // Write ImageSequence's properties.


    out->writeInt(getMode());
    out->writeDouble(getLength());

    out->writeUInt(getImageDataList().size());
    for(ImageDataList::iterator itr = getImageDataList().begin();
        itr != getImageDataList().end();
        ++itr)
    {
        out->writeString(itr->_filename);
    }

    if (getImageDataList().empty())
    {
        out->writeUInt(0);
    }

}

void ImageSequence::read(DataInputStream* in)
{
    // Peek ImageSequence's identification.
    int id = in->peekInt();
    if(id == IVEIMAGESEQUENCE){
        // Read ImageSequence's identification.
        id = in->readInt();
        // If the osg class is inherited by any other class we should also read this from file.
        osg::Object*  obj = dynamic_cast<osg::Object*>(this);
        if(obj){
            ((ive::Object*)(obj))->read(in);
        }
        else
            in_THROW_EXCEPTION("ImageSequence::read(): Could not cast this osg::ImageSequence to an osg::Object.");
        // Read ImageSequence's properties.


        setMode((osg::ImageSequence::Mode)(in->readInt()));
        setLength(in->readDouble());

        unsigned int numFileNames = in->readUInt();
        if (numFileNames>0)
        {
            if (in->getOptions()) setReadOptions(new osgDB::Options(*in->getOptions()));
            for(unsigned int i=0; i<numFileNames; ++i)
            {
                addImageFile(in->readString());
            }
        }
        else
        {
            unsigned int numImages = in->readUInt();
            for(unsigned int i=0; i<numImages; ++i)
            {
                addImage(in->readImage());
            }
        }

    }
    else{
        in_THROW_EXCEPTION("ImageSequence::read(): Expected ImageSequence identification.");
    }
}
