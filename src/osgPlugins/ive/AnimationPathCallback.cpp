﻿/**********************************************************************
 *
 *    FILE:            AnimationPathCallback.cpp
 *
 *    DESCRIPTION:    Read/Write osg::AnimationPathCallback in binary format to disk.
 *
 *    CREATED BY:        Auto generated by iveGenerate
 *                    and later modified by Rune Schmidt Jensen.
 *
 *    HISTORY:        Created 25.3.2003
 *
 *    Copyright 2003 VR-C
 **********************************************************************/

#include "Exception.h"
#include "AnimationPathCallback.h"
#include "AnimationPath.h"
#include "Object.h"

using namespace ive;

void AnimationPathCallback::write(DataOutputStream* out){
    // Write AnimationPathCallback's identification.
    out->writeInt(IVEANIMATIONPATHCALLBACK);
    // If the osg class is inherited by any other class we should also write this to file.
    osg::Object*  obj = dynamic_cast<osg::Object*>(this);
    if(obj){
        ((ive::Object*)(obj))->write(out);
    }
    else
        out_THROW_EXCEPTION("AnimationPathCallback::write(): Could not cast this osg::AnimationPathCallback to an osg::Object.");
    // Write AnimationPathCallback's properties.

    out->writeVec3(_pivotPoint);
    out->writeDouble(_timeOffset);
    out->writeDouble(_timeMultiplier);
    out->writeDouble(_firstTime);
    out->writeDouble(_pauseTime);
    // Write animationpath if any
    if(getAnimationPath())
    {
        out->writeInt(1); // true we have an animation path.
        ((ive::AnimationPath*)(getAnimationPath()))->write(out);
    }
    else
    {
        out->writeInt(0); // false we don't have an animation path.
    }
}

void AnimationPathCallback::read(DataInputStream* in){
    // Peek on AnimationPathCallback's identification.
    int id = in->peekInt();
    if(id == IVEANIMATIONPATHCALLBACK){
        // Read AnimationPathCallback's identification.
        id = in->readInt();
        // If the osg class is inherited by any other class we should also read this from file.
        osg::Object*  obj = dynamic_cast<osg::Object*>(this);
        if(obj){
            ((ive::Object*)(obj))->read(in);
        }
        else
            in_THROW_EXCEPTION("AnimationPathCallback::read(): Could not cast this osg::AnimationPathCallback to an osg::Object.");

        // Read AnimationPathCallback's properties
        _pivotPoint = in->readVec3();
        _timeOffset = in->readDouble();
        _timeMultiplier = in->readDouble();
        _firstTime = in->readDouble();
        _pauseTime = in->readDouble();
        // Read animationpath if any
        if(in->readInt())
        {
            osg::AnimationPath* path = new osg::AnimationPath();
            ((ive::AnimationPath*)(path))->read(in);
            setAnimationPath(path);
        }
    }
    else{
        in_THROW_EXCEPTION("AnimationPathCallback::read(): Expected AnimationPathCallback identification.");
    }
}
