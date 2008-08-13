/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of COLLADAStreamWriter.

    Licensed under the MIT Open Source License, 
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADASTREAMWRITER_CAMERA_OPTIC_H__
#define __COLLADASTREAMWRITER_CAMERA_OPTIC_H__

#include "COLLADAPrerequisites.h"
#include "COLLADAStreamWriter.h"
#include "COLLADAExtraTechnique.h"
#include "COLLADASWC.h"

namespace COLLADA
{

    /** A class that hold all information about an @a \<camera\> element.*/
    class BaseOptic : public ElementWriter, public BaseExtraTechnique
    {

    private:

        // Camera should be able to call the add() method.
        friend class Camera;

    protected:

        /** Flags, if the values was set. */
        bool mHasXFov;
        bool mHasYFov;
        bool mHasXMag;
        bool mHasYMag;
        bool mHasAspectRatio;
        bool mHasZNear;
        bool mHasZFar;

        /** The aspect ratio of the field of view. If the <aspect_ratio> 
        element is not specified, it is calculated from the <xfov> or <yfov> 
        elements and the current viewport. The aspect ratio is defined as the 
        ratio of the field of view�s width over its height. */
        float mAspectRatio;

        /** The distance to the near clipping plane. */
        float mZNear;

        /** The distance to the far clipping plane. */
        float mZFar;

        /** The horizontal field of view in degrees - used for the perspective camera. */
        float mXFov;

        /** The vertical field of view in degrees - used for the perspective camera. */
        float mYFov;

        /** The horizontal (X) magnification of the view. 
        The X and Y magnifications are simple scale factors, applied to the 
        X and Y components of the orthographic viewport. As such, if your 
        default orthographic viewport is [[-1,1],[-1,1]] as in OpenGL and 
        DirectX, your COLLADA orthographic viewport becomes 
        [[-xmag,xmag],[-ymag,ymag]]. This gives an orthographic width of 
        xmag/2 and an orthographic height of ymag/2. 
        - used for the orthographic camera.*/
        float mXMag;

        /** The vertical (Y) magnification of the view. 
        The X and Y magnifications are simple scale factors, applied to the 
        X and Y components of the orthographic viewport. As such, if your 
        default orthographic viewport is [[-1,1],[-1,1]] as in OpenGL and 
        DirectX, your COLLADA orthographic viewport becomes 
        [[-xmag,xmag],[-ymag,ymag]]. This gives an orthographic width of 
        xmag/2 and an orthographic height of ymag/2. 
        - used for the orthographic camera.*/
        float mYMag;

    protected:

        /** Adds the optics information. */
        void add() const;

        /** Adds the optic type specific information. */
        virtual void addTypeSpecificInfos () const = 0;

    public:

        /** 
        * Constructor
        * @param cameraId The id of the camera.
        * @param cameraName The name of the camera.
        */
        BaseOptic ( StreamWriter* streamWriter );

        /** Destructor */
        virtual ~BaseOptic() {}

        /** The distance to the far clipping plane. */
        void setZFar ( const float val ) { mZFar = val; mHasZFar = true; }

        /** The distance to the near clipping plane. */
        void setZNear ( const float val ) { mZNear = val; mHasZNear = true; }

        /** The aspect ratio of the field of view. If the <aspect_ratio> 
        element is not specified, it is calculated from the <xfov> or <yfov> 
        elements and the current viewport. The aspect ratio is defined as the 
        ratio of the field of view�s width over its height. */
        void setAspectRatio ( float val ) { mAspectRatio = val; mHasAspectRatio = true; }

        /** The horizontal field of view in degrees - used for the perspective camera. */
        void setXFov ( float val ) { mXFov = val; mHasXFov = true; }

        /** The vertical field of view in degrees - used for the perspective camera. */
        void setYFov ( float val ) { mYFov = val; mHasYFov = true; }

        /** The horizontal (X) magnification of the view. 
        The X and Y magnifications are simple scale factors, applied to the 
        X and Y components of the orthographic viewport. As such, if your 
        default orthographic viewport is [[-1,1],[-1,1]] as in OpenGL and 
        DirectX, your COLLADA orthographic viewport becomes 
        [[-xmag,xmag],[-ymag,ymag]]. This gives an orthographic width of 
        xmag/2 and an orthographic height of ymag/2. 
        - used for the orthographic camera.*/
        void setXMag ( float val ) { mXMag = val; mHasXMag = true; }

        /** The vertical (Y) magnification of the view. 
        The X and Y magnifications are simple scale factors, applied to the 
        X and Y components of the orthographic viewport. As such, if your 
        default orthographic viewport is [[-1,1],[-1,1]] as in OpenGL and 
        DirectX, your COLLADA orthographic viewport becomes 
        [[-xmag,xmag],[-ymag,ymag]]. This gives an orthographic width of 
        xmag/2 and an orthographic height of ymag/2. 
        - used for the orthographic camera.*/
        void setYMag ( float val ) { mYMag = val; mHasYMag = true; }
    };


    /** Camera class for perspective camera. 
    The projection type. The COMMON profile defines the optics types 
    <perspective> and <orthographic>. All other <optics> types must be 
    specified within a profile-specific <technique>. 
    Perspective embodies the appearance of objects relative to each other 
    as determined by their distance from a viewer. Computer graphics 
    techniques apply a perspective projection in order to render 3-D 
    objects onto 2-D surfaces to create properly proportioned images on 
    display monitors. */
    class PerspectiveOptic : public BaseOptic
    {
    public:

        /** 
        * Constructor
        * @param cameraId The id of the camera.
        * @param cameraName The name of the camera.
        */
        PerspectiveOptic ( StreamWriter* streamWriter )
        : BaseOptic ( streamWriter )
        {}

        virtual ~PerspectiveOptic() {}

    protected:

        /** Adds the camera type specific information. */
        void addTypeSpecificInfos () const;

    };

    /** Camera class for orthographic camera. 
    The COMMON profile defines the optics types 
    <perspective> and <orthographic>. All other <optics> types must be 
    specified within a profile-specific <technique>. 
    Orthographic projection describes a way of drawing a 3-D scene on a 
    2-D surface. In an orthographic projection, the apparent size of an 
    object does not depend on its distance from the camera. */
    class OrthographicOptic : public BaseOptic
    {
    public:

        /** 
        * Constructor
        */
        OrthographicOptic ( StreamWriter* streamWriter ) 
        : BaseOptic ( streamWriter ) {}

        virtual ~OrthographicOptic() {}

    protected:

        /** Adds the optic type specific information. */
        void addTypeSpecificInfos () const;

    };


} //namespace COLLADA

#endif //__COLLADASTREAMWRITER_CAMERA_OPTIC_H__