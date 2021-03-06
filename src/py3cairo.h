/* -*- mode: C; c-basic-offset: 2 -*-
 *
 * Copyright © 2003 James Henstridge
 * Copyright © 2004-2011 Steven Chaplin
 *
 * This file is part of pycairo.
 *
 * Pycairo is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3 as published
 * by the Free Software Foundation.
 *
 * Pycairo is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with pycairo. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PYCAIRO_H_
#define _PYCAIRO_H_

#include <Python.h>

#include <cairo.h>


typedef struct {
  PyObject_HEAD
  cairo_t *ctx;
  PyObject *base; /* base object used to create context, or NULL */
} PycairoContext;

typedef struct {
  PyObject_HEAD
  cairo_font_face_t *font_face;
} PycairoFontFace;

#define PycairoToyFontFace PycairoFontFace

typedef struct {
  PyObject_HEAD
  cairo_font_options_t *font_options;
} PycairoFontOptions;

typedef struct {
  PyObject_HEAD
  cairo_matrix_t matrix;
} PycairoMatrix;

typedef struct {
  PyObject_HEAD
  cairo_path_t *path;
} PycairoPath;

typedef struct {
  PyObject_HEAD
  cairo_pattern_t *pattern;
  PyObject *base; /* base object used to create pattern, or NULL */
} PycairoPattern;

#define PycairoSolidPattern   PycairoPattern
#define PycairoSurfacePattern PycairoPattern
#define PycairoGradient       PycairoPattern
#define PycairoLinearGradient PycairoPattern
#define PycairoRadialGradient PycairoPattern

typedef struct {
  PyObject_HEAD
  cairo_rectangle_int_t rectangle_int;
} PycairoRectangleInt;

typedef struct {
  PyObject_HEAD
  cairo_region_t *region;
} PycairoRegion;

typedef struct {
  PyObject_HEAD
  cairo_scaled_font_t *scaled_font;
} PycairoScaledFont;

typedef struct {
  PyObject_HEAD
  cairo_surface_t *surface;
  PyObject *base; /* base object used to create surface, or NULL */
  Py_buffer buffer;
} PycairoSurface;

#define PycairoImageSurface         PycairoSurface
#define PycairoPDFSurface           PycairoSurface
#define PycairoPSSurface            PycairoSurface
#define PycairoRecordingSurface     PycairoSurface
#define PycairoSVGSurface           PycairoSurface
#define PycairoWin32Surface         PycairoSurface
#define PycairoWin32PrintingSurface PycairoSurface
#define PycairoXCBSurface           PycairoSurface
#define PycairoXlibSurface          PycairoSurface

/* get C object out of the Python wrapper */
#define PycairoContext_GET(obj)    (((PycairoContext *)(obj))->ctx)

/* Define structure for C API. */
typedef struct {
  /* (type object, constructor) pairs */
  PyTypeObject *Context_Type;
  PyObject *(*Context_FromContext)(cairo_t *ctx, PyTypeObject *type,
				   PyObject *base);
  PyTypeObject *FontFace_Type;
  PyTypeObject *ToyFontFace_Type;
  PyObject *(*FontFace_FromFontFace)(cairo_font_face_t *font_face);
  PyTypeObject *FontOptions_Type;
  PyObject *(*FontOptions_FromFontOptions)(
					   cairo_font_options_t *font_options);
  PyTypeObject *Matrix_Type;
  PyObject *(*Matrix_FromMatrix)(const cairo_matrix_t *matrix);
  PyTypeObject *Path_Type;
  PyObject *(*Path_FromPath)(cairo_path_t *path);

  PyTypeObject *Pattern_Type;
  PyTypeObject *SolidPattern_Type;
  PyTypeObject *SurfacePattern_Type;
  PyTypeObject *Gradient_Type;
  PyTypeObject *LinearGradient_Type;
  PyTypeObject *RadialGradient_Type;
  PyObject *(*Pattern_FromPattern)(cairo_pattern_t *pattern, PyObject *base);

  PyTypeObject *ScaledFont_Type;
  PyObject *(*ScaledFont_FromScaledFont)(cairo_scaled_font_t *scaled_font);

  PyTypeObject *Surface_Type;
  PyTypeObject *ImageSurface_Type;
  PyTypeObject *PDFSurface_Type;
  PyTypeObject *PSSurface_Type;
  PyTypeObject *RecordingSurface_Type;
  PyTypeObject *SVGSurface_Type;
  PyTypeObject *Win32Surface_Type;
  PyTypeObject *Win32PrintingSurface_Type;
  PyTypeObject *XCBSurface_Type;
  PyTypeObject *XlibSurface_Type;
  PyObject *(*Surface_FromSurface)(cairo_surface_t *surface, PyObject *base);

  /* misc functions */
  int (*Check_Status)(cairo_status_t status);

  PyTypeObject *RectangleInt_Type;
  PyObject *(*RectangleInt_FromRectangleInt)(
      const cairo_rectangle_int_t *rectangle_int);

  PyTypeObject *Region_Type;
  PyObject *(*Region_FromRegion)(const cairo_region_t *region);

} Pycairo_CAPI_t;


#ifndef _INSIDE_PYCAIRO_

/* Macros for accessing the C API */
#define PycairoContext_Type         *(Pycairo_CAPI->Context_Type)
#define PycairoContext_FromContext   (Pycairo_CAPI->Context_FromContext)
#define PycairoFontFace_Type        *(Pycairo_CAPI->FontFace_Type)
#define PycairoToyFontFace_Type     *(Pycairo_CAPI->ToyFontFace_Type)
#define PycairoFontFace_FromFontFace (Pycairo_CAPI->FontFace_FromFontFace)
#define PycairoFontOptions_Type     *(Pycairo_CAPI->FontOptions_Type)
#define PycairoFontOptions_FromFontOptions \
                                    (Pycairo_CAPI->FontOptions_FromFontOptions)
#define PycairoMatrix_Type          *(Pycairo_CAPI->Matrix_Type)
#define PycairoMatrix_FromMatrix     (Pycairo_CAPI->Matrix_FromMatrix)
#define PycairoPath_Type            *(Pycairo_CAPI->Path_Type)
#define PycairoPath_FromPath         (Pycairo_CAPI->Path_FromPath)

#define PycairoPattern_Type         *(Pycairo_CAPI->Pattern_Type)
#define PycairoSolidPattern_Type    *(Pycairo_CAPI->SolidPattern_Type)
#define PycairoSurfacePattern_Type  *(Pycairo_CAPI->SurfacePattern_Type)
#define PycairoGradient_Type        *(Pycairo_CAPI->Gradient_Type)
#define PycairoLinearGradient_Type  *(Pycairo_CAPI->LinearGradient_Type)
#define PycairoRadialGradient_Type  *(Pycairo_CAPI->RadialGradient_Type)
#define PycairoPattern_FromPattern   (Pycairo_CAPI->Pattern_FromPattern)

#define PycairoRectangleInt_Type    *(Pycairo_CAPI->RectangleInt_Type)
#define PycairoRectangleInt_FromRectangleInt  \
                                  (Pycairo_CAPI->RectangleInt_FromRectangleInt)

#define PycairoRegion_Type          *(Pycairo_CAPI->Region_Type)
#define PycairoRegion_FromRegion     (Pycairo_CAPI->Region_FromRegion)

#define PycairoScaledFont_Type      *(Pycairo_CAPI->ScaledFont_Type)
#define PycairoScaledFont_FromScaledFont \
                                     (Pycairo_CAPI->ScaledFont_FromScaledFont)

#define PycairoSurface_Type         *(Pycairo_CAPI->Surface_Type)
#define PycairoImageSurface_Type    *(Pycairo_CAPI->ImageSurface_Type)

#if CAIRO_HAS_PDF_SURFACE
#define PycairoPDFSurface_Type      *(Pycairo_CAPI->PDFSurface_Type)
#endif

#if CAIRO_HAS_PS_SURFACE
#define PycairoPSSurface_Type       *(Pycairo_CAPI->PSSurface_Type)
#endif

#if CAIRO_HAS_RECORDING_SURFACE
#define PycairoRecordingSurface_Type \
                                    *(Pycairo_CAPI->RecordingSurface_Type)
#endif

#if CAIRO_HAS_SVG_SURFACE
#define PycairoSVGSurface_Type      *(Pycairo_CAPI->SVGSurface_Type)
#endif

#if CAIRO_HAS_WIN32_SURFACE
#define PycairoWin32Surface_Type    *(Pycairo_CAPI->Win32Surface_Type)
#define PycairoWin32PrintingSurface_Type    *(Pycairo_CAPI->Win32PrintingSurface_Type)
#endif

#if CAIRO_HAS_XCB_SURFACE
#define PycairoXCBSurface_Type      *(Pycairo_CAPI->XCBSurface_Type)
#endif

#if CAIRO_HAS_XLIB_SURFACE
#define PycairoXlibSurface_Type     *(Pycairo_CAPI->XlibSurface_Type)
#endif

#define PycairoSurface_FromSurface   (Pycairo_CAPI->Surface_FromSurface)

#define Pycairo_Check_Status         (Pycairo_CAPI->Check_Status)


/* To access the Pycairo C API, the client module should call 'import_cairo()'
 * from the init<module> function, and check the return value, < 0 means the
 * import failed.
 */
static Pycairo_CAPI_t *Pycairo_CAPI;

/* Return -1 on error, 0 on success.
 * PyCapsule_Import will set an exception if there's an error.
 */
static int
import_cairo(void)
{
  Pycairo_CAPI = (Pycairo_CAPI_t*) PyCapsule_Import("cairo.CAPI", 0);
  return (Pycairo_CAPI != 0) ? 0 : -1;
}

#endif /* ifndef _INSIDE_PYCAIRO_ */

#endif /* ifndef _PYCAIRO_H_ */
