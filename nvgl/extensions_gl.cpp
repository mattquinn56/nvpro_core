/*
 * Copyright (c) 2018-2021, NVIDIA CORPORATION.  All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-FileCopyrightText: Copyright (c) 2018-2021 NVIDIA CORPORATION
 * SPDX-License-Identifier: Apache-2.0
 */


#include <assert.h>
#include <cstring>
#include "extensions_gl.hpp"

/* availables */
int has_GL_VERSION_1_1 = 0;
int has_GL_VERSION_1_2 = 0;
int has_GL_VERSION_1_3 = 0;
int has_GL_VERSION_1_4 = 0;
int has_GL_VERSION_1_5 = 0;
int has_GL_VERSION_2_0 = 0;
int has_GL_VERSION_2_1 = 0;
int has_GL_VERSION_3_0 = 0;
int has_GL_VERSION_3_1 = 0;
int has_GL_VERSION_3_2 = 0;
int has_GL_VERSION_3_3 = 0;
int has_GL_VERSION_4_0 = 0;
int has_GL_VERSION_4_1 = 0;
int has_GL_VERSION_4_2 = 0;
int has_GL_VERSION_4_3 = 0;
int has_GL_VERSION_4_4 = 0;
int has_GL_VERSION_4_5 = 0;
int has_GL_VERSION_4_6 = 0;
int has_GL_ARB_bindless_texture = 0;
int has_GL_ARB_cl_event = 0;
int has_GL_ARB_debug_output = 0;
int has_GL_ARB_indirect_parameters = 0;
int has_GL_ARB_shading_language_include = 0;
int has_GL_ARB_texture_filter_minmax = 0;
int has_GL_ARB_texture_float = 0;
int has_GL_EXT_memory_object = 0;
int has_GL_EXT_memory_object_fd = 0;
int has_GL_EXT_memory_object_win32 = 0;
int has_GL_EXT_semaphore = 0;
int has_GL_EXT_semaphore_fd = 0;
int has_GL_EXT_semaphore_win32 = 0;
int has_GL_EXT_texture_compression_latc = 0;
int has_GL_EXT_texture_compression_s3tc = 0;
int has_GL_NV_bindless_texture = 0;
int has_GL_NV_blend_equation_advanced = 0;
int has_GL_NV_clip_space_w_scaling = 0;
int has_GL_NV_command_list = 0;
int has_GL_NV_compute_shader_derivatives = 0;
int has_GL_NV_conservative_raster = 0;
int has_GL_NV_conservative_raster_dilate = 0;
int has_GL_NV_conservative_raster_pre_snap = 0;
int has_GL_NV_conservative_raster_pre_snap_triangles = 0;
int has_GL_NV_conservative_raster_underestimation = 0;
int has_GL_NV_draw_vulkan_image = 0;
int has_GL_NV_fill_rectangle = 0;
int has_GL_NV_fragment_coverage_to_color = 0;
int has_GL_NV_fragment_shader_barycentric = 0;
int has_GL_NV_fragment_shader_interlock = 0;
int has_GL_NV_framebuffer_mixed_samples = 0;
int has_GL_NV_gpu_multicast = 0;
int has_GL_NV_gpu_shader5 = 0;
int has_GL_NV_internalformat_sample_query = 0;
int has_GL_NV_memory_attachment = 0;
int has_GL_NV_mesh_shader = 0;
int has_GL_NV_path_rendering = 0;
int has_GL_NV_representative_fragment_test = 0;
int has_GL_NV_sample_locations = 0;
int has_GL_NV_sample_mask_override_coverage = 0;
int has_GL_NV_scissor_exclusive = 0;
int has_GL_NV_shader_atomic_int64 = 0;
int has_GL_NV_shader_buffer_load = 0;
int has_GL_NV_shader_buffer_store = 0;
int has_GL_NV_shader_texture_footprint = 0;
int has_GL_NV_shader_thread_group = 0;
int has_GL_NV_shader_thread_shuffle = 0;
int has_GL_NV_shading_rate_image = 0;
int has_GL_NV_stereo_view_rendering = 0;
int has_GL_NV_texture_multisample = 0;
int has_GL_NV_uniform_buffer_unified_memory = 0;
int has_GL_NV_vertex_buffer_unified_memory = 0;
int has_GL_NV_viewport_swizzle = 0;
int has_GL_NVX_gpu_memory_info = 0;
int has_GL_NV_query_resource = 0;
int has_GL_NV_query_resource_tag = 0;

/* tests */
static int has_extension(const char* name)
{
  GLint numExtensions = 0;
  glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
  for (int i = 0; i < numExtensions; i++) {
    const char* ext = (const char*)glGetStringi(GL_EXTENSIONS, i);
    if (strcmp(name, ext) == 0) {
      return true;
    }
  }

  return false;
}
static int has_version(int major, int minor)
{
  GLint ctx_major;
  GLint ctx_minor;
  
  glGetIntegerv(GL_MAJOR_VERSION, &ctx_major);
  glGetIntegerv(GL_MINOR_VERSION, &ctx_minor);
  
  return (ctx_major >= major && (ctx_major > major || ctx_minor >= minor));
}

/* loaders */

void load_GL(nvGLLoaderGetProcFN fnGetProcAddress)
{
  has_GL_VERSION_1_1 = load_GL_VERSION_1_1(fnGetProcAddress);
  has_GL_VERSION_1_2 = load_GL_VERSION_1_2(fnGetProcAddress);
  has_GL_VERSION_1_3 = load_GL_VERSION_1_3(fnGetProcAddress);
  has_GL_VERSION_1_4 = load_GL_VERSION_1_4(fnGetProcAddress);
  has_GL_VERSION_1_5 = load_GL_VERSION_1_5(fnGetProcAddress);
  has_GL_VERSION_2_0 = load_GL_VERSION_2_0(fnGetProcAddress);
  has_GL_VERSION_2_1 = load_GL_VERSION_2_1(fnGetProcAddress);
  has_GL_VERSION_3_0 = load_GL_VERSION_3_0(fnGetProcAddress);
  has_GL_VERSION_3_1 = load_GL_VERSION_3_1(fnGetProcAddress);
  has_GL_VERSION_3_2 = load_GL_VERSION_3_2(fnGetProcAddress);
  has_GL_VERSION_3_3 = load_GL_VERSION_3_3(fnGetProcAddress);
  has_GL_VERSION_4_0 = load_GL_VERSION_4_0(fnGetProcAddress);
  has_GL_VERSION_4_1 = load_GL_VERSION_4_1(fnGetProcAddress);
  has_GL_VERSION_4_2 = load_GL_VERSION_4_2(fnGetProcAddress);
  has_GL_VERSION_4_3 = load_GL_VERSION_4_3(fnGetProcAddress);
  has_GL_VERSION_4_4 = load_GL_VERSION_4_4(fnGetProcAddress);
  has_GL_VERSION_4_5 = load_GL_VERSION_4_5(fnGetProcAddress);
  has_GL_VERSION_4_6 = load_GL_VERSION_4_6(fnGetProcAddress);
  has_GL_ARB_bindless_texture = load_GL_ARB_bindless_texture(fnGetProcAddress);
  has_GL_ARB_cl_event = load_GL_ARB_cl_event(fnGetProcAddress);
  has_GL_ARB_debug_output = load_GL_ARB_debug_output(fnGetProcAddress);
  has_GL_ARB_indirect_parameters = load_GL_ARB_indirect_parameters(fnGetProcAddress);
  has_GL_ARB_shading_language_include = load_GL_ARB_shading_language_include(fnGetProcAddress);
  has_GL_ARB_texture_filter_minmax = load_GL_ARB_texture_filter_minmax(fnGetProcAddress);
  has_GL_ARB_texture_float = load_GL_ARB_texture_float(fnGetProcAddress);
  has_GL_EXT_memory_object = load_GL_EXT_memory_object(fnGetProcAddress);
  has_GL_EXT_memory_object_fd = load_GL_EXT_memory_object_fd(fnGetProcAddress);
  has_GL_EXT_memory_object_win32 = load_GL_EXT_memory_object_win32(fnGetProcAddress);
  has_GL_EXT_semaphore = load_GL_EXT_semaphore(fnGetProcAddress);
  has_GL_EXT_semaphore_fd = load_GL_EXT_semaphore_fd(fnGetProcAddress);
  has_GL_EXT_semaphore_win32 = load_GL_EXT_semaphore_win32(fnGetProcAddress);
  has_GL_EXT_texture_compression_latc = load_GL_EXT_texture_compression_latc(fnGetProcAddress);
  has_GL_EXT_texture_compression_s3tc = load_GL_EXT_texture_compression_s3tc(fnGetProcAddress);
  has_GL_NV_bindless_texture = load_GL_NV_bindless_texture(fnGetProcAddress);
  has_GL_NV_blend_equation_advanced = load_GL_NV_blend_equation_advanced(fnGetProcAddress);
  has_GL_NV_clip_space_w_scaling = load_GL_NV_clip_space_w_scaling(fnGetProcAddress);
  has_GL_NV_command_list = load_GL_NV_command_list(fnGetProcAddress);
  has_GL_NV_compute_shader_derivatives = load_GL_NV_compute_shader_derivatives(fnGetProcAddress);
  has_GL_NV_conservative_raster = load_GL_NV_conservative_raster(fnGetProcAddress);
  has_GL_NV_conservative_raster_dilate = load_GL_NV_conservative_raster_dilate(fnGetProcAddress);
  has_GL_NV_conservative_raster_pre_snap = load_GL_NV_conservative_raster_pre_snap(fnGetProcAddress);
  has_GL_NV_conservative_raster_pre_snap_triangles = load_GL_NV_conservative_raster_pre_snap_triangles(fnGetProcAddress);
  has_GL_NV_conservative_raster_underestimation = load_GL_NV_conservative_raster_underestimation(fnGetProcAddress);
  has_GL_NV_draw_vulkan_image = load_GL_NV_draw_vulkan_image(fnGetProcAddress);
  has_GL_NV_fill_rectangle = load_GL_NV_fill_rectangle(fnGetProcAddress);
  has_GL_NV_fragment_coverage_to_color = load_GL_NV_fragment_coverage_to_color(fnGetProcAddress);
  has_GL_NV_fragment_shader_barycentric = load_GL_NV_fragment_shader_barycentric(fnGetProcAddress);
  has_GL_NV_fragment_shader_interlock = load_GL_NV_fragment_shader_interlock(fnGetProcAddress);
  has_GL_NV_framebuffer_mixed_samples = load_GL_NV_framebuffer_mixed_samples(fnGetProcAddress);
  has_GL_NV_gpu_multicast = load_GL_NV_gpu_multicast(fnGetProcAddress);
  has_GL_NV_gpu_shader5 = load_GL_NV_gpu_shader5(fnGetProcAddress);
  has_GL_NV_internalformat_sample_query = load_GL_NV_internalformat_sample_query(fnGetProcAddress);
  has_GL_NV_memory_attachment = load_GL_NV_memory_attachment(fnGetProcAddress);
  has_GL_NV_mesh_shader = load_GL_NV_mesh_shader(fnGetProcAddress);
  has_GL_NV_path_rendering = load_GL_NV_path_rendering(fnGetProcAddress);
  has_GL_NV_representative_fragment_test = load_GL_NV_representative_fragment_test(fnGetProcAddress);
  has_GL_NV_sample_locations = load_GL_NV_sample_locations(fnGetProcAddress);
  has_GL_NV_sample_mask_override_coverage = load_GL_NV_sample_mask_override_coverage(fnGetProcAddress);
  has_GL_NV_scissor_exclusive = load_GL_NV_scissor_exclusive(fnGetProcAddress);
  has_GL_NV_shader_atomic_int64 = load_GL_NV_shader_atomic_int64(fnGetProcAddress);
  has_GL_NV_shader_buffer_load = load_GL_NV_shader_buffer_load(fnGetProcAddress);
  has_GL_NV_shader_buffer_store = load_GL_NV_shader_buffer_store(fnGetProcAddress);
  has_GL_NV_shader_texture_footprint = load_GL_NV_shader_texture_footprint(fnGetProcAddress);
  has_GL_NV_shader_thread_group = load_GL_NV_shader_thread_group(fnGetProcAddress);
  has_GL_NV_shader_thread_shuffle = load_GL_NV_shader_thread_shuffle(fnGetProcAddress);
  has_GL_NV_shading_rate_image = load_GL_NV_shading_rate_image(fnGetProcAddress);
  has_GL_NV_stereo_view_rendering = load_GL_NV_stereo_view_rendering(fnGetProcAddress);
  has_GL_NV_texture_multisample = load_GL_NV_texture_multisample(fnGetProcAddress);
  has_GL_NV_uniform_buffer_unified_memory = load_GL_NV_uniform_buffer_unified_memory(fnGetProcAddress);
  has_GL_NV_vertex_buffer_unified_memory = load_GL_NV_vertex_buffer_unified_memory(fnGetProcAddress);
  has_GL_NV_viewport_swizzle = load_GL_NV_viewport_swizzle(fnGetProcAddress);
  has_GL_NVX_gpu_memory_info = load_GL_NVX_gpu_memory_info(fnGetProcAddress);
  has_GL_NV_query_resource = load_GL_NV_query_resource(fnGetProcAddress);
  has_GL_NV_query_resource_tag = load_GL_NV_query_resource_tag(fnGetProcAddress);
}

/* loaders */
/* /////////////////////////////////// */
/* GL_VERSION_1_1 */



int load_GL_VERSION_1_1(nvGLLoaderGetProcFN fnGetProcAddress)
{
  int success = has_version(1,1);
  return success;
}

/* /////////////////////////////////// */
/* GL_VERSION_1_2 */

static PFNGLDRAWRANGEELEMENTSPROC pfn_glDrawRangeElements = 0;
static PFNGLTEXIMAGE3DPROC pfn_glTexImage3D = 0;
static PFNGLTEXSUBIMAGE3DPROC pfn_glTexSubImage3D = 0;
static PFNGLCOPYTEXSUBIMAGE3DPROC pfn_glCopyTexSubImage3D = 0;

GLAPI void APIENTRY glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices)
{
  assert(pfn_glDrawRangeElements);
  pfn_glDrawRangeElements(mode,start,end,count,type,indices);
}
GLAPI void APIENTRY glTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* pixels)
{
  assert(pfn_glTexImage3D);
  pfn_glTexImage3D(target,level,internalformat,width,height,depth,border,format,type,pixels);
}
GLAPI void APIENTRY glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels)
{
  assert(pfn_glTexSubImage3D);
  pfn_glTexSubImage3D(target,level,xoffset,yoffset,zoffset,width,height,depth,format,type,pixels);
}
GLAPI void APIENTRY glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
  assert(pfn_glCopyTexSubImage3D);
  pfn_glCopyTexSubImage3D(target,level,xoffset,yoffset,zoffset,x,y,width,height);
}

int load_GL_VERSION_1_2(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC)fnGetProcAddress("glDrawRangeElements");
  pfn_glTexImage3D = (PFNGLTEXIMAGE3DPROC)fnGetProcAddress("glTexImage3D");
  pfn_glTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC)fnGetProcAddress("glTexSubImage3D");
  pfn_glCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC)fnGetProcAddress("glCopyTexSubImage3D");
  int success = has_version(1,2);
  success = success && (pfn_glDrawRangeElements != 0);
  success = success && (pfn_glTexImage3D != 0);
  success = success && (pfn_glTexSubImage3D != 0);
  success = success && (pfn_glCopyTexSubImage3D != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_VERSION_1_3 */

static PFNGLACTIVETEXTUREPROC pfn_glActiveTexture = 0;
static PFNGLSAMPLECOVERAGEPROC pfn_glSampleCoverage = 0;
static PFNGLCOMPRESSEDTEXIMAGE3DPROC pfn_glCompressedTexImage3D = 0;
static PFNGLCOMPRESSEDTEXIMAGE2DPROC pfn_glCompressedTexImage2D = 0;
static PFNGLCOMPRESSEDTEXIMAGE1DPROC pfn_glCompressedTexImage1D = 0;
static PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC pfn_glCompressedTexSubImage3D = 0;
static PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC pfn_glCompressedTexSubImage2D = 0;
static PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC pfn_glCompressedTexSubImage1D = 0;
static PFNGLGETCOMPRESSEDTEXIMAGEPROC pfn_glGetCompressedTexImage = 0;

GLAPI void APIENTRY glActiveTexture(GLenum texture)
{
  assert(pfn_glActiveTexture);
  pfn_glActiveTexture(texture);
}
GLAPI void APIENTRY glSampleCoverage(GLfloat value, GLboolean invert)
{
  assert(pfn_glSampleCoverage);
  pfn_glSampleCoverage(value,invert);
}
GLAPI void APIENTRY glCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void* data)
{
  assert(pfn_glCompressedTexImage3D);
  pfn_glCompressedTexImage3D(target,level,internalformat,width,height,depth,border,imageSize,data);
}
GLAPI void APIENTRY glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data)
{
  assert(pfn_glCompressedTexImage2D);
  pfn_glCompressedTexImage2D(target,level,internalformat,width,height,border,imageSize,data);
}
GLAPI void APIENTRY glCompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void* data)
{
  assert(pfn_glCompressedTexImage1D);
  pfn_glCompressedTexImage1D(target,level,internalformat,width,border,imageSize,data);
}
GLAPI void APIENTRY glCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data)
{
  assert(pfn_glCompressedTexSubImage3D);
  pfn_glCompressedTexSubImage3D(target,level,xoffset,yoffset,zoffset,width,height,depth,format,imageSize,data);
}
GLAPI void APIENTRY glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data)
{
  assert(pfn_glCompressedTexSubImage2D);
  pfn_glCompressedTexSubImage2D(target,level,xoffset,yoffset,width,height,format,imageSize,data);
}
GLAPI void APIENTRY glCompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data)
{
  assert(pfn_glCompressedTexSubImage1D);
  pfn_glCompressedTexSubImage1D(target,level,xoffset,width,format,imageSize,data);
}
GLAPI void APIENTRY glGetCompressedTexImage(GLenum target, GLint level, void* img)
{
  assert(pfn_glGetCompressedTexImage);
  pfn_glGetCompressedTexImage(target,level,img);
}

int load_GL_VERSION_1_3(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glActiveTexture = (PFNGLACTIVETEXTUREPROC)fnGetProcAddress("glActiveTexture");
  pfn_glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC)fnGetProcAddress("glSampleCoverage");
  pfn_glCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC)fnGetProcAddress("glCompressedTexImage3D");
  pfn_glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)fnGetProcAddress("glCompressedTexImage2D");
  pfn_glCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1DPROC)fnGetProcAddress("glCompressedTexImage1D");
  pfn_glCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)fnGetProcAddress("glCompressedTexSubImage3D");
  pfn_glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)fnGetProcAddress("glCompressedTexSubImage2D");
  pfn_glCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)fnGetProcAddress("glCompressedTexSubImage1D");
  pfn_glGetCompressedTexImage = (PFNGLGETCOMPRESSEDTEXIMAGEPROC)fnGetProcAddress("glGetCompressedTexImage");
  int success = has_version(1,3);
  success = success && (pfn_glActiveTexture != 0);
  success = success && (pfn_glSampleCoverage != 0);
  success = success && (pfn_glCompressedTexImage3D != 0);
  success = success && (pfn_glCompressedTexImage2D != 0);
  success = success && (pfn_glCompressedTexImage1D != 0);
  success = success && (pfn_glCompressedTexSubImage3D != 0);
  success = success && (pfn_glCompressedTexSubImage2D != 0);
  success = success && (pfn_glCompressedTexSubImage1D != 0);
  success = success && (pfn_glGetCompressedTexImage != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_VERSION_1_4 */

static PFNGLBLENDFUNCSEPARATEPROC pfn_glBlendFuncSeparate = 0;
static PFNGLMULTIDRAWARRAYSPROC pfn_glMultiDrawArrays = 0;
static PFNGLMULTIDRAWELEMENTSPROC pfn_glMultiDrawElements = 0;
static PFNGLPOINTPARAMETERFPROC pfn_glPointParameterf = 0;
static PFNGLPOINTPARAMETERFVPROC pfn_glPointParameterfv = 0;
static PFNGLPOINTPARAMETERIPROC pfn_glPointParameteri = 0;
static PFNGLPOINTPARAMETERIVPROC pfn_glPointParameteriv = 0;
static PFNGLBLENDCOLORPROC pfn_glBlendColor = 0;
static PFNGLBLENDEQUATIONPROC pfn_glBlendEquation = 0;

GLAPI void APIENTRY glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
{
  assert(pfn_glBlendFuncSeparate);
  pfn_glBlendFuncSeparate(sfactorRGB,dfactorRGB,sfactorAlpha,dfactorAlpha);
}
GLAPI void APIENTRY glMultiDrawArrays(GLenum mode, const GLint* first, const GLsizei* count, GLsizei drawcount)
{
  assert(pfn_glMultiDrawArrays);
  pfn_glMultiDrawArrays(mode,first,count,drawcount);
}
GLAPI void APIENTRY glMultiDrawElements(GLenum mode, const GLsizei* count, GLenum type, const void* const* indices, GLsizei drawcount)
{
  assert(pfn_glMultiDrawElements);
  pfn_glMultiDrawElements(mode,count,type,indices,drawcount);
}
GLAPI void APIENTRY glPointParameterf(GLenum pname, GLfloat param)
{
  assert(pfn_glPointParameterf);
  pfn_glPointParameterf(pname,param);
}
GLAPI void APIENTRY glPointParameterfv(GLenum pname, const GLfloat* params)
{
  assert(pfn_glPointParameterfv);
  pfn_glPointParameterfv(pname,params);
}
GLAPI void APIENTRY glPointParameteri(GLenum pname, GLint param)
{
  assert(pfn_glPointParameteri);
  pfn_glPointParameteri(pname,param);
}
GLAPI void APIENTRY glPointParameteriv(GLenum pname, const GLint* params)
{
  assert(pfn_glPointParameteriv);
  pfn_glPointParameteriv(pname,params);
}
GLAPI void APIENTRY glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
  assert(pfn_glBlendColor);
  pfn_glBlendColor(red,green,blue,alpha);
}
GLAPI void APIENTRY glBlendEquation(GLenum mode)
{
  assert(pfn_glBlendEquation);
  pfn_glBlendEquation(mode);
}

int load_GL_VERSION_1_4(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)fnGetProcAddress("glBlendFuncSeparate");
  pfn_glMultiDrawArrays = (PFNGLMULTIDRAWARRAYSPROC)fnGetProcAddress("glMultiDrawArrays");
  pfn_glMultiDrawElements = (PFNGLMULTIDRAWELEMENTSPROC)fnGetProcAddress("glMultiDrawElements");
  pfn_glPointParameterf = (PFNGLPOINTPARAMETERFPROC)fnGetProcAddress("glPointParameterf");
  pfn_glPointParameterfv = (PFNGLPOINTPARAMETERFVPROC)fnGetProcAddress("glPointParameterfv");
  pfn_glPointParameteri = (PFNGLPOINTPARAMETERIPROC)fnGetProcAddress("glPointParameteri");
  pfn_glPointParameteriv = (PFNGLPOINTPARAMETERIVPROC)fnGetProcAddress("glPointParameteriv");
  pfn_glBlendColor = (PFNGLBLENDCOLORPROC)fnGetProcAddress("glBlendColor");
  pfn_glBlendEquation = (PFNGLBLENDEQUATIONPROC)fnGetProcAddress("glBlendEquation");
  int success = has_version(1,4);
  success = success && (pfn_glBlendFuncSeparate != 0);
  success = success && (pfn_glMultiDrawArrays != 0);
  success = success && (pfn_glMultiDrawElements != 0);
  success = success && (pfn_glPointParameterf != 0);
  success = success && (pfn_glPointParameterfv != 0);
  success = success && (pfn_glPointParameteri != 0);
  success = success && (pfn_glPointParameteriv != 0);
  success = success && (pfn_glBlendColor != 0);
  success = success && (pfn_glBlendEquation != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_VERSION_1_5 */

static PFNGLGENQUERIESPROC pfn_glGenQueries = 0;
static PFNGLDELETEQUERIESPROC pfn_glDeleteQueries = 0;
static PFNGLISQUERYPROC pfn_glIsQuery = 0;
static PFNGLBEGINQUERYPROC pfn_glBeginQuery = 0;
static PFNGLENDQUERYPROC pfn_glEndQuery = 0;
static PFNGLGETQUERYIVPROC pfn_glGetQueryiv = 0;
static PFNGLGETQUERYOBJECTIVPROC pfn_glGetQueryObjectiv = 0;
static PFNGLGETQUERYOBJECTUIVPROC pfn_glGetQueryObjectuiv = 0;
static PFNGLBINDBUFFERPROC pfn_glBindBuffer = 0;
static PFNGLDELETEBUFFERSPROC pfn_glDeleteBuffers = 0;
static PFNGLGENBUFFERSPROC pfn_glGenBuffers = 0;
static PFNGLISBUFFERPROC pfn_glIsBuffer = 0;
static PFNGLBUFFERDATAPROC pfn_glBufferData = 0;
static PFNGLBUFFERSUBDATAPROC pfn_glBufferSubData = 0;
static PFNGLGETBUFFERSUBDATAPROC pfn_glGetBufferSubData = 0;
static PFNGLMAPBUFFERPROC pfn_glMapBuffer = 0;
static PFNGLUNMAPBUFFERPROC pfn_glUnmapBuffer = 0;
static PFNGLGETBUFFERPARAMETERIVPROC pfn_glGetBufferParameteriv = 0;
static PFNGLGETBUFFERPOINTERVPROC pfn_glGetBufferPointerv = 0;

GLAPI void APIENTRY glGenQueries(GLsizei n, GLuint* ids)
{
  assert(pfn_glGenQueries);
  pfn_glGenQueries(n,ids);
}
GLAPI void APIENTRY glDeleteQueries(GLsizei n, const GLuint* ids)
{
  assert(pfn_glDeleteQueries);
  pfn_glDeleteQueries(n,ids);
}
GLAPI GLboolean APIENTRY glIsQuery(GLuint id)
{
  assert(pfn_glIsQuery);
  return pfn_glIsQuery(id);
}
GLAPI void APIENTRY glBeginQuery(GLenum target, GLuint id)
{
  assert(pfn_glBeginQuery);
  pfn_glBeginQuery(target,id);
}
GLAPI void APIENTRY glEndQuery(GLenum target)
{
  assert(pfn_glEndQuery);
  pfn_glEndQuery(target);
}
GLAPI void APIENTRY glGetQueryiv(GLenum target, GLenum pname, GLint* params)
{
  assert(pfn_glGetQueryiv);
  pfn_glGetQueryiv(target,pname,params);
}
GLAPI void APIENTRY glGetQueryObjectiv(GLuint id, GLenum pname, GLint* params)
{
  assert(pfn_glGetQueryObjectiv);
  pfn_glGetQueryObjectiv(id,pname,params);
}
GLAPI void APIENTRY glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint* params)
{
  assert(pfn_glGetQueryObjectuiv);
  pfn_glGetQueryObjectuiv(id,pname,params);
}
GLAPI void APIENTRY glBindBuffer(GLenum target, GLuint buffer)
{
  assert(pfn_glBindBuffer);
  pfn_glBindBuffer(target,buffer);
}
GLAPI void APIENTRY glDeleteBuffers(GLsizei n, const GLuint* buffers)
{
  assert(pfn_glDeleteBuffers);
  pfn_glDeleteBuffers(n,buffers);
}
GLAPI void APIENTRY glGenBuffers(GLsizei n, GLuint* buffers)
{
  assert(pfn_glGenBuffers);
  pfn_glGenBuffers(n,buffers);
}
GLAPI GLboolean APIENTRY glIsBuffer(GLuint buffer)
{
  assert(pfn_glIsBuffer);
  return pfn_glIsBuffer(buffer);
}
GLAPI void APIENTRY glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
{
  assert(pfn_glBufferData);
  pfn_glBufferData(target,size,data,usage);
}
GLAPI void APIENTRY glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data)
{
  assert(pfn_glBufferSubData);
  pfn_glBufferSubData(target,offset,size,data);
}
GLAPI void APIENTRY glGetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, void* data)
{
  assert(pfn_glGetBufferSubData);
  pfn_glGetBufferSubData(target,offset,size,data);
}
GLAPI void* APIENTRY glMapBuffer(GLenum target, GLenum access)
{
  assert(pfn_glMapBuffer);
  return pfn_glMapBuffer(target,access);
}
GLAPI GLboolean APIENTRY glUnmapBuffer(GLenum target)
{
  assert(pfn_glUnmapBuffer);
  return pfn_glUnmapBuffer(target);
}
GLAPI void APIENTRY glGetBufferParameteriv(GLenum target, GLenum pname, GLint* params)
{
  assert(pfn_glGetBufferParameteriv);
  pfn_glGetBufferParameteriv(target,pname,params);
}
GLAPI void APIENTRY glGetBufferPointerv(GLenum target, GLenum pname, void* * params)
{
  assert(pfn_glGetBufferPointerv);
  pfn_glGetBufferPointerv(target,pname,params);
}

int load_GL_VERSION_1_5(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glGenQueries = (PFNGLGENQUERIESPROC)fnGetProcAddress("glGenQueries");
  pfn_glDeleteQueries = (PFNGLDELETEQUERIESPROC)fnGetProcAddress("glDeleteQueries");
  pfn_glIsQuery = (PFNGLISQUERYPROC)fnGetProcAddress("glIsQuery");
  pfn_glBeginQuery = (PFNGLBEGINQUERYPROC)fnGetProcAddress("glBeginQuery");
  pfn_glEndQuery = (PFNGLENDQUERYPROC)fnGetProcAddress("glEndQuery");
  pfn_glGetQueryiv = (PFNGLGETQUERYIVPROC)fnGetProcAddress("glGetQueryiv");
  pfn_glGetQueryObjectiv = (PFNGLGETQUERYOBJECTIVPROC)fnGetProcAddress("glGetQueryObjectiv");
  pfn_glGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC)fnGetProcAddress("glGetQueryObjectuiv");
  pfn_glBindBuffer = (PFNGLBINDBUFFERPROC)fnGetProcAddress("glBindBuffer");
  pfn_glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)fnGetProcAddress("glDeleteBuffers");
  pfn_glGenBuffers = (PFNGLGENBUFFERSPROC)fnGetProcAddress("glGenBuffers");
  pfn_glIsBuffer = (PFNGLISBUFFERPROC)fnGetProcAddress("glIsBuffer");
  pfn_glBufferData = (PFNGLBUFFERDATAPROC)fnGetProcAddress("glBufferData");
  pfn_glBufferSubData = (PFNGLBUFFERSUBDATAPROC)fnGetProcAddress("glBufferSubData");
  pfn_glGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC)fnGetProcAddress("glGetBufferSubData");
  pfn_glMapBuffer = (PFNGLMAPBUFFERPROC)fnGetProcAddress("glMapBuffer");
  pfn_glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)fnGetProcAddress("glUnmapBuffer");
  pfn_glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)fnGetProcAddress("glGetBufferParameteriv");
  pfn_glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC)fnGetProcAddress("glGetBufferPointerv");
  int success = has_version(1,5);
  success = success && (pfn_glGenQueries != 0);
  success = success && (pfn_glDeleteQueries != 0);
  success = success && (pfn_glIsQuery != 0);
  success = success && (pfn_glBeginQuery != 0);
  success = success && (pfn_glEndQuery != 0);
  success = success && (pfn_glGetQueryiv != 0);
  success = success && (pfn_glGetQueryObjectiv != 0);
  success = success && (pfn_glGetQueryObjectuiv != 0);
  success = success && (pfn_glBindBuffer != 0);
  success = success && (pfn_glDeleteBuffers != 0);
  success = success && (pfn_glGenBuffers != 0);
  success = success && (pfn_glIsBuffer != 0);
  success = success && (pfn_glBufferData != 0);
  success = success && (pfn_glBufferSubData != 0);
  success = success && (pfn_glGetBufferSubData != 0);
  success = success && (pfn_glMapBuffer != 0);
  success = success && (pfn_glUnmapBuffer != 0);
  success = success && (pfn_glGetBufferParameteriv != 0);
  success = success && (pfn_glGetBufferPointerv != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_VERSION_2_0 */

static PFNGLBLENDEQUATIONSEPARATEPROC pfn_glBlendEquationSeparate = 0;
static PFNGLDRAWBUFFERSPROC pfn_glDrawBuffers = 0;
static PFNGLSTENCILOPSEPARATEPROC pfn_glStencilOpSeparate = 0;
static PFNGLSTENCILFUNCSEPARATEPROC pfn_glStencilFuncSeparate = 0;
static PFNGLSTENCILMASKSEPARATEPROC pfn_glStencilMaskSeparate = 0;
static PFNGLATTACHSHADERPROC pfn_glAttachShader = 0;
static PFNGLBINDATTRIBLOCATIONPROC pfn_glBindAttribLocation = 0;
static PFNGLCOMPILESHADERPROC pfn_glCompileShader = 0;
static PFNGLCREATEPROGRAMPROC pfn_glCreateProgram = 0;
static PFNGLCREATESHADERPROC pfn_glCreateShader = 0;
static PFNGLDELETEPROGRAMPROC pfn_glDeleteProgram = 0;
static PFNGLDELETESHADERPROC pfn_glDeleteShader = 0;
static PFNGLDETACHSHADERPROC pfn_glDetachShader = 0;
static PFNGLDISABLEVERTEXATTRIBARRAYPROC pfn_glDisableVertexAttribArray = 0;
static PFNGLENABLEVERTEXATTRIBARRAYPROC pfn_glEnableVertexAttribArray = 0;
static PFNGLGETACTIVEATTRIBPROC pfn_glGetActiveAttrib = 0;
static PFNGLGETACTIVEUNIFORMPROC pfn_glGetActiveUniform = 0;
static PFNGLGETATTACHEDSHADERSPROC pfn_glGetAttachedShaders = 0;
static PFNGLGETATTRIBLOCATIONPROC pfn_glGetAttribLocation = 0;
static PFNGLGETPROGRAMIVPROC pfn_glGetProgramiv = 0;
static PFNGLGETPROGRAMINFOLOGPROC pfn_glGetProgramInfoLog = 0;
static PFNGLGETSHADERIVPROC pfn_glGetShaderiv = 0;
static PFNGLGETSHADERINFOLOGPROC pfn_glGetShaderInfoLog = 0;
static PFNGLGETSHADERSOURCEPROC pfn_glGetShaderSource = 0;
static PFNGLGETUNIFORMLOCATIONPROC pfn_glGetUniformLocation = 0;
static PFNGLGETUNIFORMFVPROC pfn_glGetUniformfv = 0;
static PFNGLGETUNIFORMIVPROC pfn_glGetUniformiv = 0;
static PFNGLGETVERTEXATTRIBDVPROC pfn_glGetVertexAttribdv = 0;
static PFNGLGETVERTEXATTRIBFVPROC pfn_glGetVertexAttribfv = 0;
static PFNGLGETVERTEXATTRIBIVPROC pfn_glGetVertexAttribiv = 0;
static PFNGLGETVERTEXATTRIBPOINTERVPROC pfn_glGetVertexAttribPointerv = 0;
static PFNGLISPROGRAMPROC pfn_glIsProgram = 0;
static PFNGLISSHADERPROC pfn_glIsShader = 0;
static PFNGLLINKPROGRAMPROC pfn_glLinkProgram = 0;
static PFNGLSHADERSOURCEPROC pfn_glShaderSource = 0;
static PFNGLUSEPROGRAMPROC pfn_glUseProgram = 0;
static PFNGLUNIFORM1FPROC pfn_glUniform1f = 0;
static PFNGLUNIFORM2FPROC pfn_glUniform2f = 0;
static PFNGLUNIFORM3FPROC pfn_glUniform3f = 0;
static PFNGLUNIFORM4FPROC pfn_glUniform4f = 0;
static PFNGLUNIFORM1IPROC pfn_glUniform1i = 0;
static PFNGLUNIFORM2IPROC pfn_glUniform2i = 0;
static PFNGLUNIFORM3IPROC pfn_glUniform3i = 0;
static PFNGLUNIFORM4IPROC pfn_glUniform4i = 0;
static PFNGLUNIFORM1FVPROC pfn_glUniform1fv = 0;
static PFNGLUNIFORM2FVPROC pfn_glUniform2fv = 0;
static PFNGLUNIFORM3FVPROC pfn_glUniform3fv = 0;
static PFNGLUNIFORM4FVPROC pfn_glUniform4fv = 0;
static PFNGLUNIFORM1IVPROC pfn_glUniform1iv = 0;
static PFNGLUNIFORM2IVPROC pfn_glUniform2iv = 0;
static PFNGLUNIFORM3IVPROC pfn_glUniform3iv = 0;
static PFNGLUNIFORM4IVPROC pfn_glUniform4iv = 0;
static PFNGLUNIFORMMATRIX2FVPROC pfn_glUniformMatrix2fv = 0;
static PFNGLUNIFORMMATRIX3FVPROC pfn_glUniformMatrix3fv = 0;
static PFNGLUNIFORMMATRIX4FVPROC pfn_glUniformMatrix4fv = 0;
static PFNGLVALIDATEPROGRAMPROC pfn_glValidateProgram = 0;
static PFNGLVERTEXATTRIB1DPROC pfn_glVertexAttrib1d = 0;
static PFNGLVERTEXATTRIB1DVPROC pfn_glVertexAttrib1dv = 0;
static PFNGLVERTEXATTRIB1FPROC pfn_glVertexAttrib1f = 0;
static PFNGLVERTEXATTRIB1FVPROC pfn_glVertexAttrib1fv = 0;
static PFNGLVERTEXATTRIB1SPROC pfn_glVertexAttrib1s = 0;
static PFNGLVERTEXATTRIB1SVPROC pfn_glVertexAttrib1sv = 0;
static PFNGLVERTEXATTRIB2DPROC pfn_glVertexAttrib2d = 0;
static PFNGLVERTEXATTRIB2DVPROC pfn_glVertexAttrib2dv = 0;
static PFNGLVERTEXATTRIB2FPROC pfn_glVertexAttrib2f = 0;
static PFNGLVERTEXATTRIB2FVPROC pfn_glVertexAttrib2fv = 0;
static PFNGLVERTEXATTRIB2SPROC pfn_glVertexAttrib2s = 0;
static PFNGLVERTEXATTRIB2SVPROC pfn_glVertexAttrib2sv = 0;
static PFNGLVERTEXATTRIB3DPROC pfn_glVertexAttrib3d = 0;
static PFNGLVERTEXATTRIB3DVPROC pfn_glVertexAttrib3dv = 0;
static PFNGLVERTEXATTRIB3FPROC pfn_glVertexAttrib3f = 0;
static PFNGLVERTEXATTRIB3FVPROC pfn_glVertexAttrib3fv = 0;
static PFNGLVERTEXATTRIB3SPROC pfn_glVertexAttrib3s = 0;
static PFNGLVERTEXATTRIB3SVPROC pfn_glVertexAttrib3sv = 0;
static PFNGLVERTEXATTRIB4NBVPROC pfn_glVertexAttrib4Nbv = 0;
static PFNGLVERTEXATTRIB4NIVPROC pfn_glVertexAttrib4Niv = 0;
static PFNGLVERTEXATTRIB4NSVPROC pfn_glVertexAttrib4Nsv = 0;
static PFNGLVERTEXATTRIB4NUBPROC pfn_glVertexAttrib4Nub = 0;
static PFNGLVERTEXATTRIB4NUBVPROC pfn_glVertexAttrib4Nubv = 0;
static PFNGLVERTEXATTRIB4NUIVPROC pfn_glVertexAttrib4Nuiv = 0;
static PFNGLVERTEXATTRIB4NUSVPROC pfn_glVertexAttrib4Nusv = 0;
static PFNGLVERTEXATTRIB4BVPROC pfn_glVertexAttrib4bv = 0;
static PFNGLVERTEXATTRIB4DPROC pfn_glVertexAttrib4d = 0;
static PFNGLVERTEXATTRIB4DVPROC pfn_glVertexAttrib4dv = 0;
static PFNGLVERTEXATTRIB4FPROC pfn_glVertexAttrib4f = 0;
static PFNGLVERTEXATTRIB4FVPROC pfn_glVertexAttrib4fv = 0;
static PFNGLVERTEXATTRIB4IVPROC pfn_glVertexAttrib4iv = 0;
static PFNGLVERTEXATTRIB4SPROC pfn_glVertexAttrib4s = 0;
static PFNGLVERTEXATTRIB4SVPROC pfn_glVertexAttrib4sv = 0;
static PFNGLVERTEXATTRIB4UBVPROC pfn_glVertexAttrib4ubv = 0;
static PFNGLVERTEXATTRIB4UIVPROC pfn_glVertexAttrib4uiv = 0;
static PFNGLVERTEXATTRIB4USVPROC pfn_glVertexAttrib4usv = 0;
static PFNGLVERTEXATTRIBPOINTERPROC pfn_glVertexAttribPointer = 0;

GLAPI void APIENTRY glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
  assert(pfn_glBlendEquationSeparate);
  pfn_glBlendEquationSeparate(modeRGB,modeAlpha);
}
GLAPI void APIENTRY glDrawBuffers(GLsizei n, const GLenum* bufs)
{
  assert(pfn_glDrawBuffers);
  pfn_glDrawBuffers(n,bufs);
}
GLAPI void APIENTRY glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass)
{
  assert(pfn_glStencilOpSeparate);
  pfn_glStencilOpSeparate(face,sfail,dpfail,dppass);
}
GLAPI void APIENTRY glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
{
  assert(pfn_glStencilFuncSeparate);
  pfn_glStencilFuncSeparate(face,func,ref,mask);
}
GLAPI void APIENTRY glStencilMaskSeparate(GLenum face, GLuint mask)
{
  assert(pfn_glStencilMaskSeparate);
  pfn_glStencilMaskSeparate(face,mask);
}
GLAPI void APIENTRY glAttachShader(GLuint program, GLuint shader)
{
  assert(pfn_glAttachShader);
  pfn_glAttachShader(program,shader);
}
GLAPI void APIENTRY glBindAttribLocation(GLuint program, GLuint index, const GLchar* name)
{
  assert(pfn_glBindAttribLocation);
  pfn_glBindAttribLocation(program,index,name);
}
GLAPI void APIENTRY glCompileShader(GLuint shader)
{
  assert(pfn_glCompileShader);
  pfn_glCompileShader(shader);
}
GLAPI GLuint APIENTRY glCreateProgram(void)
{
  assert(pfn_glCreateProgram);
  return pfn_glCreateProgram();
}
GLAPI GLuint APIENTRY glCreateShader(GLenum type)
{
  assert(pfn_glCreateShader);
  return pfn_glCreateShader(type);
}
GLAPI void APIENTRY glDeleteProgram(GLuint program)
{
  assert(pfn_glDeleteProgram);
  pfn_glDeleteProgram(program);
}
GLAPI void APIENTRY glDeleteShader(GLuint shader)
{
  assert(pfn_glDeleteShader);
  pfn_glDeleteShader(shader);
}
GLAPI void APIENTRY glDetachShader(GLuint program, GLuint shader)
{
  assert(pfn_glDetachShader);
  pfn_glDetachShader(program,shader);
}
GLAPI void APIENTRY glDisableVertexAttribArray(GLuint index)
{
  assert(pfn_glDisableVertexAttribArray);
  pfn_glDisableVertexAttribArray(index);
}
GLAPI void APIENTRY glEnableVertexAttribArray(GLuint index)
{
  assert(pfn_glEnableVertexAttribArray);
  pfn_glEnableVertexAttribArray(index);
}
GLAPI void APIENTRY glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
{
  assert(pfn_glGetActiveAttrib);
  pfn_glGetActiveAttrib(program,index,bufSize,length,size,type,name);
}
GLAPI void APIENTRY glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
{
  assert(pfn_glGetActiveUniform);
  pfn_glGetActiveUniform(program,index,bufSize,length,size,type,name);
}
GLAPI void APIENTRY glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei* count, GLuint* shaders)
{
  assert(pfn_glGetAttachedShaders);
  pfn_glGetAttachedShaders(program,maxCount,count,shaders);
}
GLAPI GLint APIENTRY glGetAttribLocation(GLuint program, const GLchar* name)
{
  assert(pfn_glGetAttribLocation);
  return pfn_glGetAttribLocation(program,name);
}
GLAPI void APIENTRY glGetProgramiv(GLuint program, GLenum pname, GLint* params)
{
  assert(pfn_glGetProgramiv);
  pfn_glGetProgramiv(program,pname,params);
}
GLAPI void APIENTRY glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
{
  assert(pfn_glGetProgramInfoLog);
  pfn_glGetProgramInfoLog(program,bufSize,length,infoLog);
}
GLAPI void APIENTRY glGetShaderiv(GLuint shader, GLenum pname, GLint* params)
{
  assert(pfn_glGetShaderiv);
  pfn_glGetShaderiv(shader,pname,params);
}
GLAPI void APIENTRY glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
{
  assert(pfn_glGetShaderInfoLog);
  pfn_glGetShaderInfoLog(shader,bufSize,length,infoLog);
}
GLAPI void APIENTRY glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* source)
{
  assert(pfn_glGetShaderSource);
  pfn_glGetShaderSource(shader,bufSize,length,source);
}
GLAPI GLint APIENTRY glGetUniformLocation(GLuint program, const GLchar* name)
{
  assert(pfn_glGetUniformLocation);
  return pfn_glGetUniformLocation(program,name);
}
GLAPI void APIENTRY glGetUniformfv(GLuint program, GLint location, GLfloat* params)
{
  assert(pfn_glGetUniformfv);
  pfn_glGetUniformfv(program,location,params);
}
GLAPI void APIENTRY glGetUniformiv(GLuint program, GLint location, GLint* params)
{
  assert(pfn_glGetUniformiv);
  pfn_glGetUniformiv(program,location,params);
}
GLAPI void APIENTRY glGetVertexAttribdv(GLuint index, GLenum pname, GLdouble* params)
{
  assert(pfn_glGetVertexAttribdv);
  pfn_glGetVertexAttribdv(index,pname,params);
}
GLAPI void APIENTRY glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params)
{
  assert(pfn_glGetVertexAttribfv);
  pfn_glGetVertexAttribfv(index,pname,params);
}
GLAPI void APIENTRY glGetVertexAttribiv(GLuint index, GLenum pname, GLint* params)
{
  assert(pfn_glGetVertexAttribiv);
  pfn_glGetVertexAttribiv(index,pname,params);
}
GLAPI void APIENTRY glGetVertexAttribPointerv(GLuint index, GLenum pname, void* * pointer)
{
  assert(pfn_glGetVertexAttribPointerv);
  pfn_glGetVertexAttribPointerv(index,pname,pointer);
}
GLAPI GLboolean APIENTRY glIsProgram(GLuint program)
{
  assert(pfn_glIsProgram);
  return pfn_glIsProgram(program);
}
GLAPI GLboolean APIENTRY glIsShader(GLuint shader)
{
  assert(pfn_glIsShader);
  return pfn_glIsShader(shader);
}
GLAPI void APIENTRY glLinkProgram(GLuint program)
{
  assert(pfn_glLinkProgram);
  pfn_glLinkProgram(program);
}
GLAPI void APIENTRY glShaderSource(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length)
{
  assert(pfn_glShaderSource);
  pfn_glShaderSource(shader,count,string,length);
}
GLAPI void APIENTRY glUseProgram(GLuint program)
{
  assert(pfn_glUseProgram);
  pfn_glUseProgram(program);
}
GLAPI void APIENTRY glUniform1f(GLint location, GLfloat v0)
{
  assert(pfn_glUniform1f);
  pfn_glUniform1f(location,v0);
}
GLAPI void APIENTRY glUniform2f(GLint location, GLfloat v0, GLfloat v1)
{
  assert(pfn_glUniform2f);
  pfn_glUniform2f(location,v0,v1);
}
GLAPI void APIENTRY glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
  assert(pfn_glUniform3f);
  pfn_glUniform3f(location,v0,v1,v2);
}
GLAPI void APIENTRY glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
  assert(pfn_glUniform4f);
  pfn_glUniform4f(location,v0,v1,v2,v3);
}
GLAPI void APIENTRY glUniform1i(GLint location, GLint v0)
{
  assert(pfn_glUniform1i);
  pfn_glUniform1i(location,v0);
}
GLAPI void APIENTRY glUniform2i(GLint location, GLint v0, GLint v1)
{
  assert(pfn_glUniform2i);
  pfn_glUniform2i(location,v0,v1);
}
GLAPI void APIENTRY glUniform3i(GLint location, GLint v0, GLint v1, GLint v2)
{
  assert(pfn_glUniform3i);
  pfn_glUniform3i(location,v0,v1,v2);
}
GLAPI void APIENTRY glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
  assert(pfn_glUniform4i);
  pfn_glUniform4i(location,v0,v1,v2,v3);
}
GLAPI void APIENTRY glUniform1fv(GLint location, GLsizei count, const GLfloat* value)
{
  assert(pfn_glUniform1fv);
  pfn_glUniform1fv(location,count,value);
}
GLAPI void APIENTRY glUniform2fv(GLint location, GLsizei count, const GLfloat* value)
{
  assert(pfn_glUniform2fv);
  pfn_glUniform2fv(location,count,value);
}
GLAPI void APIENTRY glUniform3fv(GLint location, GLsizei count, const GLfloat* value)
{
  assert(pfn_glUniform3fv);
  pfn_glUniform3fv(location,count,value);
}
GLAPI void APIENTRY glUniform4fv(GLint location, GLsizei count, const GLfloat* value)
{
  assert(pfn_glUniform4fv);
  pfn_glUniform4fv(location,count,value);
}
GLAPI void APIENTRY glUniform1iv(GLint location, GLsizei count, const GLint* value)
{
  assert(pfn_glUniform1iv);
  pfn_glUniform1iv(location,count,value);
}
GLAPI void APIENTRY glUniform2iv(GLint location, GLsizei count, const GLint* value)
{
  assert(pfn_glUniform2iv);
  pfn_glUniform2iv(location,count,value);
}
GLAPI void APIENTRY glUniform3iv(GLint location, GLsizei count, const GLint* value)
{
  assert(pfn_glUniform3iv);
  pfn_glUniform3iv(location,count,value);
}
GLAPI void APIENTRY glUniform4iv(GLint location, GLsizei count, const GLint* value)
{
  assert(pfn_glUniform4iv);
  pfn_glUniform4iv(location,count,value);
}
GLAPI void APIENTRY glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  assert(pfn_glUniformMatrix2fv);
  pfn_glUniformMatrix2fv(location,count,transpose,value);
}
GLAPI void APIENTRY glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  assert(pfn_glUniformMatrix3fv);
  pfn_glUniformMatrix3fv(location,count,transpose,value);
}
GLAPI void APIENTRY glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  assert(pfn_glUniformMatrix4fv);
  pfn_glUniformMatrix4fv(location,count,transpose,value);
}
GLAPI void APIENTRY glValidateProgram(GLuint program)
{
  assert(pfn_glValidateProgram);
  pfn_glValidateProgram(program);
}
GLAPI void APIENTRY glVertexAttrib1d(GLuint index, GLdouble x)
{
  assert(pfn_glVertexAttrib1d);
  pfn_glVertexAttrib1d(index,x);
}
GLAPI void APIENTRY glVertexAttrib1dv(GLuint index, const GLdouble* v)
{
  assert(pfn_glVertexAttrib1dv);
  pfn_glVertexAttrib1dv(index,v);
}
GLAPI void APIENTRY glVertexAttrib1f(GLuint index, GLfloat x)
{
  assert(pfn_glVertexAttrib1f);
  pfn_glVertexAttrib1f(index,x);
}
GLAPI void APIENTRY glVertexAttrib1fv(GLuint index, const GLfloat* v)
{
  assert(pfn_glVertexAttrib1fv);
  pfn_glVertexAttrib1fv(index,v);
}
GLAPI void APIENTRY glVertexAttrib1s(GLuint index, GLshort x)
{
  assert(pfn_glVertexAttrib1s);
  pfn_glVertexAttrib1s(index,x);
}
GLAPI void APIENTRY glVertexAttrib1sv(GLuint index, const GLshort* v)
{
  assert(pfn_glVertexAttrib1sv);
  pfn_glVertexAttrib1sv(index,v);
}
GLAPI void APIENTRY glVertexAttrib2d(GLuint index, GLdouble x, GLdouble y)
{
  assert(pfn_glVertexAttrib2d);
  pfn_glVertexAttrib2d(index,x,y);
}
GLAPI void APIENTRY glVertexAttrib2dv(GLuint index, const GLdouble* v)
{
  assert(pfn_glVertexAttrib2dv);
  pfn_glVertexAttrib2dv(index,v);
}
GLAPI void APIENTRY glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y)
{
  assert(pfn_glVertexAttrib2f);
  pfn_glVertexAttrib2f(index,x,y);
}
GLAPI void APIENTRY glVertexAttrib2fv(GLuint index, const GLfloat* v)
{
  assert(pfn_glVertexAttrib2fv);
  pfn_glVertexAttrib2fv(index,v);
}
GLAPI void APIENTRY glVertexAttrib2s(GLuint index, GLshort x, GLshort y)
{
  assert(pfn_glVertexAttrib2s);
  pfn_glVertexAttrib2s(index,x,y);
}
GLAPI void APIENTRY glVertexAttrib2sv(GLuint index, const GLshort* v)
{
  assert(pfn_glVertexAttrib2sv);
  pfn_glVertexAttrib2sv(index,v);
}
GLAPI void APIENTRY glVertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z)
{
  assert(pfn_glVertexAttrib3d);
  pfn_glVertexAttrib3d(index,x,y,z);
}
GLAPI void APIENTRY glVertexAttrib3dv(GLuint index, const GLdouble* v)
{
  assert(pfn_glVertexAttrib3dv);
  pfn_glVertexAttrib3dv(index,v);
}
GLAPI void APIENTRY glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z)
{
  assert(pfn_glVertexAttrib3f);
  pfn_glVertexAttrib3f(index,x,y,z);
}
GLAPI void APIENTRY glVertexAttrib3fv(GLuint index, const GLfloat* v)
{
  assert(pfn_glVertexAttrib3fv);
  pfn_glVertexAttrib3fv(index,v);
}
GLAPI void APIENTRY glVertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z)
{
  assert(pfn_glVertexAttrib3s);
  pfn_glVertexAttrib3s(index,x,y,z);
}
GLAPI void APIENTRY glVertexAttrib3sv(GLuint index, const GLshort* v)
{
  assert(pfn_glVertexAttrib3sv);
  pfn_glVertexAttrib3sv(index,v);
}
GLAPI void APIENTRY glVertexAttrib4Nbv(GLuint index, const GLbyte* v)
{
  assert(pfn_glVertexAttrib4Nbv);
  pfn_glVertexAttrib4Nbv(index,v);
}
GLAPI void APIENTRY glVertexAttrib4Niv(GLuint index, const GLint* v)
{
  assert(pfn_glVertexAttrib4Niv);
  pfn_glVertexAttrib4Niv(index,v);
}
GLAPI void APIENTRY glVertexAttrib4Nsv(GLuint index, const GLshort* v)
{
  assert(pfn_glVertexAttrib4Nsv);
  pfn_glVertexAttrib4Nsv(index,v);
}
GLAPI void APIENTRY glVertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w)
{
  assert(pfn_glVertexAttrib4Nub);
  pfn_glVertexAttrib4Nub(index,x,y,z,w);
}
GLAPI void APIENTRY glVertexAttrib4Nubv(GLuint index, const GLubyte* v)
{
  assert(pfn_glVertexAttrib4Nubv);
  pfn_glVertexAttrib4Nubv(index,v);
}
GLAPI void APIENTRY glVertexAttrib4Nuiv(GLuint index, const GLuint* v)
{
  assert(pfn_glVertexAttrib4Nuiv);
  pfn_glVertexAttrib4Nuiv(index,v);
}
GLAPI void APIENTRY glVertexAttrib4Nusv(GLuint index, const GLushort* v)
{
  assert(pfn_glVertexAttrib4Nusv);
  pfn_glVertexAttrib4Nusv(index,v);
}
GLAPI void APIENTRY glVertexAttrib4bv(GLuint index, const GLbyte* v)
{
  assert(pfn_glVertexAttrib4bv);
  pfn_glVertexAttrib4bv(index,v);
}
GLAPI void APIENTRY glVertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
  assert(pfn_glVertexAttrib4d);
  pfn_glVertexAttrib4d(index,x,y,z,w);
}
GLAPI void APIENTRY glVertexAttrib4dv(GLuint index, const GLdouble* v)
{
  assert(pfn_glVertexAttrib4dv);
  pfn_glVertexAttrib4dv(index,v);
}
GLAPI void APIENTRY glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
  assert(pfn_glVertexAttrib4f);
  pfn_glVertexAttrib4f(index,x,y,z,w);
}
GLAPI void APIENTRY glVertexAttrib4fv(GLuint index, const GLfloat* v)
{
  assert(pfn_glVertexAttrib4fv);
  pfn_glVertexAttrib4fv(index,v);
}
GLAPI void APIENTRY glVertexAttrib4iv(GLuint index, const GLint* v)
{
  assert(pfn_glVertexAttrib4iv);
  pfn_glVertexAttrib4iv(index,v);
}
GLAPI void APIENTRY glVertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w)
{
  assert(pfn_glVertexAttrib4s);
  pfn_glVertexAttrib4s(index,x,y,z,w);
}
GLAPI void APIENTRY glVertexAttrib4sv(GLuint index, const GLshort* v)
{
  assert(pfn_glVertexAttrib4sv);
  pfn_glVertexAttrib4sv(index,v);
}
GLAPI void APIENTRY glVertexAttrib4ubv(GLuint index, const GLubyte* v)
{
  assert(pfn_glVertexAttrib4ubv);
  pfn_glVertexAttrib4ubv(index,v);
}
GLAPI void APIENTRY glVertexAttrib4uiv(GLuint index, const GLuint* v)
{
  assert(pfn_glVertexAttrib4uiv);
  pfn_glVertexAttrib4uiv(index,v);
}
GLAPI void APIENTRY glVertexAttrib4usv(GLuint index, const GLushort* v)
{
  assert(pfn_glVertexAttrib4usv);
  pfn_glVertexAttrib4usv(index,v);
}
GLAPI void APIENTRY glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
  assert(pfn_glVertexAttribPointer);
  pfn_glVertexAttribPointer(index,size,type,normalized,stride,pointer);
}

int load_GL_VERSION_2_0(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)fnGetProcAddress("glBlendEquationSeparate");
  pfn_glDrawBuffers = (PFNGLDRAWBUFFERSPROC)fnGetProcAddress("glDrawBuffers");
  pfn_glStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC)fnGetProcAddress("glStencilOpSeparate");
  pfn_glStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC)fnGetProcAddress("glStencilFuncSeparate");
  pfn_glStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC)fnGetProcAddress("glStencilMaskSeparate");
  pfn_glAttachShader = (PFNGLATTACHSHADERPROC)fnGetProcAddress("glAttachShader");
  pfn_glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)fnGetProcAddress("glBindAttribLocation");
  pfn_glCompileShader = (PFNGLCOMPILESHADERPROC)fnGetProcAddress("glCompileShader");
  pfn_glCreateProgram = (PFNGLCREATEPROGRAMPROC)fnGetProcAddress("glCreateProgram");
  pfn_glCreateShader = (PFNGLCREATESHADERPROC)fnGetProcAddress("glCreateShader");
  pfn_glDeleteProgram = (PFNGLDELETEPROGRAMPROC)fnGetProcAddress("glDeleteProgram");
  pfn_glDeleteShader = (PFNGLDELETESHADERPROC)fnGetProcAddress("glDeleteShader");
  pfn_glDetachShader = (PFNGLDETACHSHADERPROC)fnGetProcAddress("glDetachShader");
  pfn_glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)fnGetProcAddress("glDisableVertexAttribArray");
  pfn_glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)fnGetProcAddress("glEnableVertexAttribArray");
  pfn_glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC)fnGetProcAddress("glGetActiveAttrib");
  pfn_glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)fnGetProcAddress("glGetActiveUniform");
  pfn_glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC)fnGetProcAddress("glGetAttachedShaders");
  pfn_glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)fnGetProcAddress("glGetAttribLocation");
  pfn_glGetProgramiv = (PFNGLGETPROGRAMIVPROC)fnGetProcAddress("glGetProgramiv");
  pfn_glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)fnGetProcAddress("glGetProgramInfoLog");
  pfn_glGetShaderiv = (PFNGLGETSHADERIVPROC)fnGetProcAddress("glGetShaderiv");
  pfn_glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)fnGetProcAddress("glGetShaderInfoLog");
  pfn_glGetShaderSource = (PFNGLGETSHADERSOURCEPROC)fnGetProcAddress("glGetShaderSource");
  pfn_glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)fnGetProcAddress("glGetUniformLocation");
  pfn_glGetUniformfv = (PFNGLGETUNIFORMFVPROC)fnGetProcAddress("glGetUniformfv");
  pfn_glGetUniformiv = (PFNGLGETUNIFORMIVPROC)fnGetProcAddress("glGetUniformiv");
  pfn_glGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDVPROC)fnGetProcAddress("glGetVertexAttribdv");
  pfn_glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC)fnGetProcAddress("glGetVertexAttribfv");
  pfn_glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC)fnGetProcAddress("glGetVertexAttribiv");
  pfn_glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC)fnGetProcAddress("glGetVertexAttribPointerv");
  pfn_glIsProgram = (PFNGLISPROGRAMPROC)fnGetProcAddress("glIsProgram");
  pfn_glIsShader = (PFNGLISSHADERPROC)fnGetProcAddress("glIsShader");
  pfn_glLinkProgram = (PFNGLLINKPROGRAMPROC)fnGetProcAddress("glLinkProgram");
  pfn_glShaderSource = (PFNGLSHADERSOURCEPROC)fnGetProcAddress("glShaderSource");
  pfn_glUseProgram = (PFNGLUSEPROGRAMPROC)fnGetProcAddress("glUseProgram");
  pfn_glUniform1f = (PFNGLUNIFORM1FPROC)fnGetProcAddress("glUniform1f");
  pfn_glUniform2f = (PFNGLUNIFORM2FPROC)fnGetProcAddress("glUniform2f");
  pfn_glUniform3f = (PFNGLUNIFORM3FPROC)fnGetProcAddress("glUniform3f");
  pfn_glUniform4f = (PFNGLUNIFORM4FPROC)fnGetProcAddress("glUniform4f");
  pfn_glUniform1i = (PFNGLUNIFORM1IPROC)fnGetProcAddress("glUniform1i");
  pfn_glUniform2i = (PFNGLUNIFORM2IPROC)fnGetProcAddress("glUniform2i");
  pfn_glUniform3i = (PFNGLUNIFORM3IPROC)fnGetProcAddress("glUniform3i");
  pfn_glUniform4i = (PFNGLUNIFORM4IPROC)fnGetProcAddress("glUniform4i");
  pfn_glUniform1fv = (PFNGLUNIFORM1FVPROC)fnGetProcAddress("glUniform1fv");
  pfn_glUniform2fv = (PFNGLUNIFORM2FVPROC)fnGetProcAddress("glUniform2fv");
  pfn_glUniform3fv = (PFNGLUNIFORM3FVPROC)fnGetProcAddress("glUniform3fv");
  pfn_glUniform4fv = (PFNGLUNIFORM4FVPROC)fnGetProcAddress("glUniform4fv");
  pfn_glUniform1iv = (PFNGLUNIFORM1IVPROC)fnGetProcAddress("glUniform1iv");
  pfn_glUniform2iv = (PFNGLUNIFORM2IVPROC)fnGetProcAddress("glUniform2iv");
  pfn_glUniform3iv = (PFNGLUNIFORM3IVPROC)fnGetProcAddress("glUniform3iv");
  pfn_glUniform4iv = (PFNGLUNIFORM4IVPROC)fnGetProcAddress("glUniform4iv");
  pfn_glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)fnGetProcAddress("glUniformMatrix2fv");
  pfn_glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)fnGetProcAddress("glUniformMatrix3fv");
  pfn_glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)fnGetProcAddress("glUniformMatrix4fv");
  pfn_glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)fnGetProcAddress("glValidateProgram");
  pfn_glVertexAttrib1d = (PFNGLVERTEXATTRIB1DPROC)fnGetProcAddress("glVertexAttrib1d");
  pfn_glVertexAttrib1dv = (PFNGLVERTEXATTRIB1DVPROC)fnGetProcAddress("glVertexAttrib1dv");
  pfn_glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)fnGetProcAddress("glVertexAttrib1f");
  pfn_glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)fnGetProcAddress("glVertexAttrib1fv");
  pfn_glVertexAttrib1s = (PFNGLVERTEXATTRIB1SPROC)fnGetProcAddress("glVertexAttrib1s");
  pfn_glVertexAttrib1sv = (PFNGLVERTEXATTRIB1SVPROC)fnGetProcAddress("glVertexAttrib1sv");
  pfn_glVertexAttrib2d = (PFNGLVERTEXATTRIB2DPROC)fnGetProcAddress("glVertexAttrib2d");
  pfn_glVertexAttrib2dv = (PFNGLVERTEXATTRIB2DVPROC)fnGetProcAddress("glVertexAttrib2dv");
  pfn_glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC)fnGetProcAddress("glVertexAttrib2f");
  pfn_glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)fnGetProcAddress("glVertexAttrib2fv");
  pfn_glVertexAttrib2s = (PFNGLVERTEXATTRIB2SPROC)fnGetProcAddress("glVertexAttrib2s");
  pfn_glVertexAttrib2sv = (PFNGLVERTEXATTRIB2SVPROC)fnGetProcAddress("glVertexAttrib2sv");
  pfn_glVertexAttrib3d = (PFNGLVERTEXATTRIB3DPROC)fnGetProcAddress("glVertexAttrib3d");
  pfn_glVertexAttrib3dv = (PFNGLVERTEXATTRIB3DVPROC)fnGetProcAddress("glVertexAttrib3dv");
  pfn_glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC)fnGetProcAddress("glVertexAttrib3f");
  pfn_glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)fnGetProcAddress("glVertexAttrib3fv");
  pfn_glVertexAttrib3s = (PFNGLVERTEXATTRIB3SPROC)fnGetProcAddress("glVertexAttrib3s");
  pfn_glVertexAttrib3sv = (PFNGLVERTEXATTRIB3SVPROC)fnGetProcAddress("glVertexAttrib3sv");
  pfn_glVertexAttrib4Nbv = (PFNGLVERTEXATTRIB4NBVPROC)fnGetProcAddress("glVertexAttrib4Nbv");
  pfn_glVertexAttrib4Niv = (PFNGLVERTEXATTRIB4NIVPROC)fnGetProcAddress("glVertexAttrib4Niv");
  pfn_glVertexAttrib4Nsv = (PFNGLVERTEXATTRIB4NSVPROC)fnGetProcAddress("glVertexAttrib4Nsv");
  pfn_glVertexAttrib4Nub = (PFNGLVERTEXATTRIB4NUBPROC)fnGetProcAddress("glVertexAttrib4Nub");
  pfn_glVertexAttrib4Nubv = (PFNGLVERTEXATTRIB4NUBVPROC)fnGetProcAddress("glVertexAttrib4Nubv");
  pfn_glVertexAttrib4Nuiv = (PFNGLVERTEXATTRIB4NUIVPROC)fnGetProcAddress("glVertexAttrib4Nuiv");
  pfn_glVertexAttrib4Nusv = (PFNGLVERTEXATTRIB4NUSVPROC)fnGetProcAddress("glVertexAttrib4Nusv");
  pfn_glVertexAttrib4bv = (PFNGLVERTEXATTRIB4BVPROC)fnGetProcAddress("glVertexAttrib4bv");
  pfn_glVertexAttrib4d = (PFNGLVERTEXATTRIB4DPROC)fnGetProcAddress("glVertexAttrib4d");
  pfn_glVertexAttrib4dv = (PFNGLVERTEXATTRIB4DVPROC)fnGetProcAddress("glVertexAttrib4dv");
  pfn_glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC)fnGetProcAddress("glVertexAttrib4f");
  pfn_glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)fnGetProcAddress("glVertexAttrib4fv");
  pfn_glVertexAttrib4iv = (PFNGLVERTEXATTRIB4IVPROC)fnGetProcAddress("glVertexAttrib4iv");
  pfn_glVertexAttrib4s = (PFNGLVERTEXATTRIB4SPROC)fnGetProcAddress("glVertexAttrib4s");
  pfn_glVertexAttrib4sv = (PFNGLVERTEXATTRIB4SVPROC)fnGetProcAddress("glVertexAttrib4sv");
  pfn_glVertexAttrib4ubv = (PFNGLVERTEXATTRIB4UBVPROC)fnGetProcAddress("glVertexAttrib4ubv");
  pfn_glVertexAttrib4uiv = (PFNGLVERTEXATTRIB4UIVPROC)fnGetProcAddress("glVertexAttrib4uiv");
  pfn_glVertexAttrib4usv = (PFNGLVERTEXATTRIB4USVPROC)fnGetProcAddress("glVertexAttrib4usv");
  pfn_glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)fnGetProcAddress("glVertexAttribPointer");
  int success = has_version(2,0);
  success = success && (pfn_glBlendEquationSeparate != 0);
  success = success && (pfn_glDrawBuffers != 0);
  success = success && (pfn_glStencilOpSeparate != 0);
  success = success && (pfn_glStencilFuncSeparate != 0);
  success = success && (pfn_glStencilMaskSeparate != 0);
  success = success && (pfn_glAttachShader != 0);
  success = success && (pfn_glBindAttribLocation != 0);
  success = success && (pfn_glCompileShader != 0);
  success = success && (pfn_glCreateProgram != 0);
  success = success && (pfn_glCreateShader != 0);
  success = success && (pfn_glDeleteProgram != 0);
  success = success && (pfn_glDeleteShader != 0);
  success = success && (pfn_glDetachShader != 0);
  success = success && (pfn_glDisableVertexAttribArray != 0);
  success = success && (pfn_glEnableVertexAttribArray != 0);
  success = success && (pfn_glGetActiveAttrib != 0);
  success = success && (pfn_glGetActiveUniform != 0);
  success = success && (pfn_glGetAttachedShaders != 0);
  success = success && (pfn_glGetAttribLocation != 0);
  success = success && (pfn_glGetProgramiv != 0);
  success = success && (pfn_glGetProgramInfoLog != 0);
  success = success && (pfn_glGetShaderiv != 0);
  success = success && (pfn_glGetShaderInfoLog != 0);
  success = success && (pfn_glGetShaderSource != 0);
  success = success && (pfn_glGetUniformLocation != 0);
  success = success && (pfn_glGetUniformfv != 0);
  success = success && (pfn_glGetUniformiv != 0);
  success = success && (pfn_glGetVertexAttribdv != 0);
  success = success && (pfn_glGetVertexAttribfv != 0);
  success = success && (pfn_glGetVertexAttribiv != 0);
  success = success && (pfn_glGetVertexAttribPointerv != 0);
  success = success && (pfn_glIsProgram != 0);
  success = success && (pfn_glIsShader != 0);
  success = success && (pfn_glLinkProgram != 0);
  success = success && (pfn_glShaderSource != 0);
  success = success && (pfn_glUseProgram != 0);
  success = success && (pfn_glUniform1f != 0);
  success = success && (pfn_glUniform2f != 0);
  success = success && (pfn_glUniform3f != 0);
  success = success && (pfn_glUniform4f != 0);
  success = success && (pfn_glUniform1i != 0);
  success = success && (pfn_glUniform2i != 0);
  success = success && (pfn_glUniform3i != 0);
  success = success && (pfn_glUniform4i != 0);
  success = success && (pfn_glUniform1fv != 0);
  success = success && (pfn_glUniform2fv != 0);
  success = success && (pfn_glUniform3fv != 0);
  success = success && (pfn_glUniform4fv != 0);
  success = success && (pfn_glUniform1iv != 0);
  success = success && (pfn_glUniform2iv != 0);
  success = success && (pfn_glUniform3iv != 0);
  success = success && (pfn_glUniform4iv != 0);
  success = success && (pfn_glUniformMatrix2fv != 0);
  success = success && (pfn_glUniformMatrix3fv != 0);
  success = success && (pfn_glUniformMatrix4fv != 0);
  success = success && (pfn_glValidateProgram != 0);
  success = success && (pfn_glVertexAttrib1d != 0);
  success = success && (pfn_glVertexAttrib1dv != 0);
  success = success && (pfn_glVertexAttrib1f != 0);
  success = success && (pfn_glVertexAttrib1fv != 0);
  success = success && (pfn_glVertexAttrib1s != 0);
  success = success && (pfn_glVertexAttrib1sv != 0);
  success = success && (pfn_glVertexAttrib2d != 0);
  success = success && (pfn_glVertexAttrib2dv != 0);
  success = success && (pfn_glVertexAttrib2f != 0);
  success = success && (pfn_glVertexAttrib2fv != 0);
  success = success && (pfn_glVertexAttrib2s != 0);
  success = success && (pfn_glVertexAttrib2sv != 0);
  success = success && (pfn_glVertexAttrib3d != 0);
  success = success && (pfn_glVertexAttrib3dv != 0);
  success = success && (pfn_glVertexAttrib3f != 0);
  success = success && (pfn_glVertexAttrib3fv != 0);
  success = success && (pfn_glVertexAttrib3s != 0);
  success = success && (pfn_glVertexAttrib3sv != 0);
  success = success && (pfn_glVertexAttrib4Nbv != 0);
  success = success && (pfn_glVertexAttrib4Niv != 0);
  success = success && (pfn_glVertexAttrib4Nsv != 0);
  success = success && (pfn_glVertexAttrib4Nub != 0);
  success = success && (pfn_glVertexAttrib4Nubv != 0);
  success = success && (pfn_glVertexAttrib4Nuiv != 0);
  success = success && (pfn_glVertexAttrib4Nusv != 0);
  success = success && (pfn_glVertexAttrib4bv != 0);
  success = success && (pfn_glVertexAttrib4d != 0);
  success = success && (pfn_glVertexAttrib4dv != 0);
  success = success && (pfn_glVertexAttrib4f != 0);
  success = success && (pfn_glVertexAttrib4fv != 0);
  success = success && (pfn_glVertexAttrib4iv != 0);
  success = success && (pfn_glVertexAttrib4s != 0);
  success = success && (pfn_glVertexAttrib4sv != 0);
  success = success && (pfn_glVertexAttrib4ubv != 0);
  success = success && (pfn_glVertexAttrib4uiv != 0);
  success = success && (pfn_glVertexAttrib4usv != 0);
  success = success && (pfn_glVertexAttribPointer != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_VERSION_2_1 */

static PFNGLUNIFORMMATRIX2X3FVPROC pfn_glUniformMatrix2x3fv = 0;
static PFNGLUNIFORMMATRIX3X2FVPROC pfn_glUniformMatrix3x2fv = 0;
static PFNGLUNIFORMMATRIX2X4FVPROC pfn_glUniformMatrix2x4fv = 0;
static PFNGLUNIFORMMATRIX4X2FVPROC pfn_glUniformMatrix4x2fv = 0;
static PFNGLUNIFORMMATRIX3X4FVPROC pfn_glUniformMatrix3x4fv = 0;
static PFNGLUNIFORMMATRIX4X3FVPROC pfn_glUniformMatrix4x3fv = 0;

GLAPI void APIENTRY glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  assert(pfn_glUniformMatrix2x3fv);
  pfn_glUniformMatrix2x3fv(location,count,transpose,value);
}
GLAPI void APIENTRY glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  assert(pfn_glUniformMatrix3x2fv);
  pfn_glUniformMatrix3x2fv(location,count,transpose,value);
}
GLAPI void APIENTRY glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  assert(pfn_glUniformMatrix2x4fv);
  pfn_glUniformMatrix2x4fv(location,count,transpose,value);
}
GLAPI void APIENTRY glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  assert(pfn_glUniformMatrix4x2fv);
  pfn_glUniformMatrix4x2fv(location,count,transpose,value);
}
GLAPI void APIENTRY glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  assert(pfn_glUniformMatrix3x4fv);
  pfn_glUniformMatrix3x4fv(location,count,transpose,value);
}
GLAPI void APIENTRY glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  assert(pfn_glUniformMatrix4x3fv);
  pfn_glUniformMatrix4x3fv(location,count,transpose,value);
}

int load_GL_VERSION_2_1(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC)fnGetProcAddress("glUniformMatrix2x3fv");
  pfn_glUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC)fnGetProcAddress("glUniformMatrix3x2fv");
  pfn_glUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC)fnGetProcAddress("glUniformMatrix2x4fv");
  pfn_glUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC)fnGetProcAddress("glUniformMatrix4x2fv");
  pfn_glUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC)fnGetProcAddress("glUniformMatrix3x4fv");
  pfn_glUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC)fnGetProcAddress("glUniformMatrix4x3fv");
  int success = has_version(2,1);
  success = success && (pfn_glUniformMatrix2x3fv != 0);
  success = success && (pfn_glUniformMatrix3x2fv != 0);
  success = success && (pfn_glUniformMatrix2x4fv != 0);
  success = success && (pfn_glUniformMatrix4x2fv != 0);
  success = success && (pfn_glUniformMatrix3x4fv != 0);
  success = success && (pfn_glUniformMatrix4x3fv != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_VERSION_3_0 */

static PFNGLCOLORMASKIPROC pfn_glColorMaski = 0;
static PFNGLGETBOOLEANI_VPROC pfn_glGetBooleani_v = 0;
static PFNGLGETINTEGERI_VPROC pfn_glGetIntegeri_v = 0;
static PFNGLENABLEIPROC pfn_glEnablei = 0;
static PFNGLDISABLEIPROC pfn_glDisablei = 0;
static PFNGLISENABLEDIPROC pfn_glIsEnabledi = 0;
static PFNGLBEGINTRANSFORMFEEDBACKPROC pfn_glBeginTransformFeedback = 0;
static PFNGLENDTRANSFORMFEEDBACKPROC pfn_glEndTransformFeedback = 0;
static PFNGLBINDBUFFERRANGEPROC pfn_glBindBufferRange = 0;
static PFNGLBINDBUFFERBASEPROC pfn_glBindBufferBase = 0;
static PFNGLTRANSFORMFEEDBACKVARYINGSPROC pfn_glTransformFeedbackVaryings = 0;
static PFNGLGETTRANSFORMFEEDBACKVARYINGPROC pfn_glGetTransformFeedbackVarying = 0;
static PFNGLCLAMPCOLORPROC pfn_glClampColor = 0;
static PFNGLBEGINCONDITIONALRENDERPROC pfn_glBeginConditionalRender = 0;
static PFNGLENDCONDITIONALRENDERPROC pfn_glEndConditionalRender = 0;
static PFNGLVERTEXATTRIBIPOINTERPROC pfn_glVertexAttribIPointer = 0;
static PFNGLGETVERTEXATTRIBIIVPROC pfn_glGetVertexAttribIiv = 0;
static PFNGLGETVERTEXATTRIBIUIVPROC pfn_glGetVertexAttribIuiv = 0;
static PFNGLVERTEXATTRIBI1IPROC pfn_glVertexAttribI1i = 0;
static PFNGLVERTEXATTRIBI2IPROC pfn_glVertexAttribI2i = 0;
static PFNGLVERTEXATTRIBI3IPROC pfn_glVertexAttribI3i = 0;
static PFNGLVERTEXATTRIBI4IPROC pfn_glVertexAttribI4i = 0;
static PFNGLVERTEXATTRIBI1UIPROC pfn_glVertexAttribI1ui = 0;
static PFNGLVERTEXATTRIBI2UIPROC pfn_glVertexAttribI2ui = 0;
static PFNGLVERTEXATTRIBI3UIPROC pfn_glVertexAttribI3ui = 0;
static PFNGLVERTEXATTRIBI4UIPROC pfn_glVertexAttribI4ui = 0;
static PFNGLVERTEXATTRIBI1IVPROC pfn_glVertexAttribI1iv = 0;
static PFNGLVERTEXATTRIBI2IVPROC pfn_glVertexAttribI2iv = 0;
static PFNGLVERTEXATTRIBI3IVPROC pfn_glVertexAttribI3iv = 0;
static PFNGLVERTEXATTRIBI4IVPROC pfn_glVertexAttribI4iv = 0;
static PFNGLVERTEXATTRIBI1UIVPROC pfn_glVertexAttribI1uiv = 0;
static PFNGLVERTEXATTRIBI2UIVPROC pfn_glVertexAttribI2uiv = 0;
static PFNGLVERTEXATTRIBI3UIVPROC pfn_glVertexAttribI3uiv = 0;
static PFNGLVERTEXATTRIBI4UIVPROC pfn_glVertexAttribI4uiv = 0;
static PFNGLVERTEXATTRIBI4BVPROC pfn_glVertexAttribI4bv = 0;
static PFNGLVERTEXATTRIBI4SVPROC pfn_glVertexAttribI4sv = 0;
static PFNGLVERTEXATTRIBI4UBVPROC pfn_glVertexAttribI4ubv = 0;
static PFNGLVERTEXATTRIBI4USVPROC pfn_glVertexAttribI4usv = 0;
static PFNGLGETUNIFORMUIVPROC pfn_glGetUniformuiv = 0;
static PFNGLBINDFRAGDATALOCATIONPROC pfn_glBindFragDataLocation = 0;
static PFNGLGETFRAGDATALOCATIONPROC pfn_glGetFragDataLocation = 0;
static PFNGLUNIFORM1UIPROC pfn_glUniform1ui = 0;
static PFNGLUNIFORM2UIPROC pfn_glUniform2ui = 0;
static PFNGLUNIFORM3UIPROC pfn_glUniform3ui = 0;
static PFNGLUNIFORM4UIPROC pfn_glUniform4ui = 0;
static PFNGLUNIFORM1UIVPROC pfn_glUniform1uiv = 0;
static PFNGLUNIFORM2UIVPROC pfn_glUniform2uiv = 0;
static PFNGLUNIFORM3UIVPROC pfn_glUniform3uiv = 0;
static PFNGLUNIFORM4UIVPROC pfn_glUniform4uiv = 0;
static PFNGLTEXPARAMETERIIVPROC pfn_glTexParameterIiv = 0;
static PFNGLTEXPARAMETERIUIVPROC pfn_glTexParameterIuiv = 0;
static PFNGLGETTEXPARAMETERIIVPROC pfn_glGetTexParameterIiv = 0;
static PFNGLGETTEXPARAMETERIUIVPROC pfn_glGetTexParameterIuiv = 0;
static PFNGLCLEARBUFFERIVPROC pfn_glClearBufferiv = 0;
static PFNGLCLEARBUFFERUIVPROC pfn_glClearBufferuiv = 0;
static PFNGLCLEARBUFFERFVPROC pfn_glClearBufferfv = 0;
static PFNGLCLEARBUFFERFIPROC pfn_glClearBufferfi = 0;
static PFNGLGETSTRINGIPROC pfn_glGetStringi = 0;
static PFNGLISRENDERBUFFERPROC pfn_glIsRenderbuffer = 0;
static PFNGLBINDRENDERBUFFERPROC pfn_glBindRenderbuffer = 0;
static PFNGLDELETERENDERBUFFERSPROC pfn_glDeleteRenderbuffers = 0;
static PFNGLGENRENDERBUFFERSPROC pfn_glGenRenderbuffers = 0;
static PFNGLRENDERBUFFERSTORAGEPROC pfn_glRenderbufferStorage = 0;
static PFNGLGETRENDERBUFFERPARAMETERIVPROC pfn_glGetRenderbufferParameteriv = 0;
static PFNGLISFRAMEBUFFERPROC pfn_glIsFramebuffer = 0;
static PFNGLBINDFRAMEBUFFERPROC pfn_glBindFramebuffer = 0;
static PFNGLDELETEFRAMEBUFFERSPROC pfn_glDeleteFramebuffers = 0;
static PFNGLGENFRAMEBUFFERSPROC pfn_glGenFramebuffers = 0;
static PFNGLCHECKFRAMEBUFFERSTATUSPROC pfn_glCheckFramebufferStatus = 0;
static PFNGLFRAMEBUFFERTEXTURE1DPROC pfn_glFramebufferTexture1D = 0;
static PFNGLFRAMEBUFFERTEXTURE2DPROC pfn_glFramebufferTexture2D = 0;
static PFNGLFRAMEBUFFERTEXTURE3DPROC pfn_glFramebufferTexture3D = 0;
static PFNGLFRAMEBUFFERRENDERBUFFERPROC pfn_glFramebufferRenderbuffer = 0;
static PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC pfn_glGetFramebufferAttachmentParameteriv = 0;
static PFNGLGENERATEMIPMAPPROC pfn_glGenerateMipmap = 0;
static PFNGLBLITFRAMEBUFFERPROC pfn_glBlitFramebuffer = 0;
static PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC pfn_glRenderbufferStorageMultisample = 0;
static PFNGLFRAMEBUFFERTEXTURELAYERPROC pfn_glFramebufferTextureLayer = 0;
static PFNGLMAPBUFFERRANGEPROC pfn_glMapBufferRange = 0;
static PFNGLFLUSHMAPPEDBUFFERRANGEPROC pfn_glFlushMappedBufferRange = 0;
static PFNGLBINDVERTEXARRAYPROC pfn_glBindVertexArray = 0;
static PFNGLDELETEVERTEXARRAYSPROC pfn_glDeleteVertexArrays = 0;
static PFNGLGENVERTEXARRAYSPROC pfn_glGenVertexArrays = 0;
static PFNGLISVERTEXARRAYPROC pfn_glIsVertexArray = 0;

GLAPI void APIENTRY glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a)
{
  assert(pfn_glColorMaski);
  pfn_glColorMaski(index,r,g,b,a);
}
GLAPI void APIENTRY glGetBooleani_v(GLenum target, GLuint index, GLboolean* data)
{
  assert(pfn_glGetBooleani_v);
  pfn_glGetBooleani_v(target,index,data);
}
GLAPI void APIENTRY glGetIntegeri_v(GLenum target, GLuint index, GLint* data)
{
  assert(pfn_glGetIntegeri_v);
  pfn_glGetIntegeri_v(target,index,data);
}
GLAPI void APIENTRY glEnablei(GLenum target, GLuint index)
{
  assert(pfn_glEnablei);
  pfn_glEnablei(target,index);
}
GLAPI void APIENTRY glDisablei(GLenum target, GLuint index)
{
  assert(pfn_glDisablei);
  pfn_glDisablei(target,index);
}
GLAPI GLboolean APIENTRY glIsEnabledi(GLenum target, GLuint index)
{
  assert(pfn_glIsEnabledi);
  return pfn_glIsEnabledi(target,index);
}
GLAPI void APIENTRY glBeginTransformFeedback(GLenum primitiveMode)
{
  assert(pfn_glBeginTransformFeedback);
  pfn_glBeginTransformFeedback(primitiveMode);
}
GLAPI void APIENTRY glEndTransformFeedback(void)
{
  assert(pfn_glEndTransformFeedback);
  pfn_glEndTransformFeedback();
}
GLAPI void APIENTRY glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
  assert(pfn_glBindBufferRange);
  pfn_glBindBufferRange(target,index,buffer,offset,size);
}
GLAPI void APIENTRY glBindBufferBase(GLenum target, GLuint index, GLuint buffer)
{
  assert(pfn_glBindBufferBase);
  pfn_glBindBufferBase(target,index,buffer);
}
GLAPI void APIENTRY glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar* const* varyings, GLenum bufferMode)
{
  assert(pfn_glTransformFeedbackVaryings);
  pfn_glTransformFeedbackVaryings(program,count,varyings,bufferMode);
}
GLAPI void APIENTRY glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name)
{
  assert(pfn_glGetTransformFeedbackVarying);
  pfn_glGetTransformFeedbackVarying(program,index,bufSize,length,size,type,name);
}
GLAPI void APIENTRY glClampColor(GLenum target, GLenum clamp)
{
  assert(pfn_glClampColor);
  pfn_glClampColor(target,clamp);
}
GLAPI void APIENTRY glBeginConditionalRender(GLuint id, GLenum mode)
{
  assert(pfn_glBeginConditionalRender);
  pfn_glBeginConditionalRender(id,mode);
}
GLAPI void APIENTRY glEndConditionalRender(void)
{
  assert(pfn_glEndConditionalRender);
  pfn_glEndConditionalRender();
}
GLAPI void APIENTRY glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer)
{
  assert(pfn_glVertexAttribIPointer);
  pfn_glVertexAttribIPointer(index,size,type,stride,pointer);
}
GLAPI void APIENTRY glGetVertexAttribIiv(GLuint index, GLenum pname, GLint* params)
{
  assert(pfn_glGetVertexAttribIiv);
  pfn_glGetVertexAttribIiv(index,pname,params);
}
GLAPI void APIENTRY glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint* params)
{
  assert(pfn_glGetVertexAttribIuiv);
  pfn_glGetVertexAttribIuiv(index,pname,params);
}
GLAPI void APIENTRY glVertexAttribI1i(GLuint index, GLint x)
{
  assert(pfn_glVertexAttribI1i);
  pfn_glVertexAttribI1i(index,x);
}
GLAPI void APIENTRY glVertexAttribI2i(GLuint index, GLint x, GLint y)
{
  assert(pfn_glVertexAttribI2i);
  pfn_glVertexAttribI2i(index,x,y);
}
GLAPI void APIENTRY glVertexAttribI3i(GLuint index, GLint x, GLint y, GLint z)
{
  assert(pfn_glVertexAttribI3i);
  pfn_glVertexAttribI3i(index,x,y,z);
}
GLAPI void APIENTRY glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w)
{
  assert(pfn_glVertexAttribI4i);
  pfn_glVertexAttribI4i(index,x,y,z,w);
}
GLAPI void APIENTRY glVertexAttribI1ui(GLuint index, GLuint x)
{
  assert(pfn_glVertexAttribI1ui);
  pfn_glVertexAttribI1ui(index,x);
}
GLAPI void APIENTRY glVertexAttribI2ui(GLuint index, GLuint x, GLuint y)
{
  assert(pfn_glVertexAttribI2ui);
  pfn_glVertexAttribI2ui(index,x,y);
}
GLAPI void APIENTRY glVertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z)
{
  assert(pfn_glVertexAttribI3ui);
  pfn_glVertexAttribI3ui(index,x,y,z);
}
GLAPI void APIENTRY glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)
{
  assert(pfn_glVertexAttribI4ui);
  pfn_glVertexAttribI4ui(index,x,y,z,w);
}
GLAPI void APIENTRY glVertexAttribI1iv(GLuint index, const GLint* v)
{
  assert(pfn_glVertexAttribI1iv);
  pfn_glVertexAttribI1iv(index,v);
}
GLAPI void APIENTRY glVertexAttribI2iv(GLuint index, const GLint* v)
{
  assert(pfn_glVertexAttribI2iv);
  pfn_glVertexAttribI2iv(index,v);
}
GLAPI void APIENTRY glVertexAttribI3iv(GLuint index, const GLint* v)
{
  assert(pfn_glVertexAttribI3iv);
  pfn_glVertexAttribI3iv(index,v);
}
GLAPI void APIENTRY glVertexAttribI4iv(GLuint index, const GLint* v)
{
  assert(pfn_glVertexAttribI4iv);
  pfn_glVertexAttribI4iv(index,v);
}
GLAPI void APIENTRY glVertexAttribI1uiv(GLuint index, const GLuint* v)
{
  assert(pfn_glVertexAttribI1uiv);
  pfn_glVertexAttribI1uiv(index,v);
}
GLAPI void APIENTRY glVertexAttribI2uiv(GLuint index, const GLuint* v)
{
  assert(pfn_glVertexAttribI2uiv);
  pfn_glVertexAttribI2uiv(index,v);
}
GLAPI void APIENTRY glVertexAttribI3uiv(GLuint index, const GLuint* v)
{
  assert(pfn_glVertexAttribI3uiv);
  pfn_glVertexAttribI3uiv(index,v);
}
GLAPI void APIENTRY glVertexAttribI4uiv(GLuint index, const GLuint* v)
{
  assert(pfn_glVertexAttribI4uiv);
  pfn_glVertexAttribI4uiv(index,v);
}
GLAPI void APIENTRY glVertexAttribI4bv(GLuint index, const GLbyte* v)
{
  assert(pfn_glVertexAttribI4bv);
  pfn_glVertexAttribI4bv(index,v);
}
GLAPI void APIENTRY glVertexAttribI4sv(GLuint index, const GLshort* v)
{
  assert(pfn_glVertexAttribI4sv);
  pfn_glVertexAttribI4sv(index,v);
}
GLAPI void APIENTRY glVertexAttribI4ubv(GLuint index, const GLubyte* v)
{
  assert(pfn_glVertexAttribI4ubv);
  pfn_glVertexAttribI4ubv(index,v);
}
GLAPI void APIENTRY glVertexAttribI4usv(GLuint index, const GLushort* v)
{
  assert(pfn_glVertexAttribI4usv);
  pfn_glVertexAttribI4usv(index,v);
}
GLAPI void APIENTRY glGetUniformuiv(GLuint program, GLint location, GLuint* params)
{
  assert(pfn_glGetUniformuiv);
  pfn_glGetUniformuiv(program,location,params);
}
GLAPI void APIENTRY glBindFragDataLocation(GLuint program, GLuint color, const GLchar* name)
{
  assert(pfn_glBindFragDataLocation);
  pfn_glBindFragDataLocation(program,color,name);
}
GLAPI GLint APIENTRY glGetFragDataLocation(GLuint program, const GLchar* name)
{
  assert(pfn_glGetFragDataLocation);
  return pfn_glGetFragDataLocation(program,name);
}
GLAPI void APIENTRY glUniform1ui(GLint location, GLuint v0)
{
  assert(pfn_glUniform1ui);
  pfn_glUniform1ui(location,v0);
}
GLAPI void APIENTRY glUniform2ui(GLint location, GLuint v0, GLuint v1)
{
  assert(pfn_glUniform2ui);
  pfn_glUniform2ui(location,v0,v1);
}
GLAPI void APIENTRY glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2)
{
  assert(pfn_glUniform3ui);
  pfn_glUniform3ui(location,v0,v1,v2);
}
GLAPI void APIENTRY glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
  assert(pfn_glUniform4ui);
  pfn_glUniform4ui(location,v0,v1,v2,v3);
}
GLAPI void APIENTRY glUniform1uiv(GLint location, GLsizei count, const GLuint* value)
{
  assert(pfn_glUniform1uiv);
  pfn_glUniform1uiv(location,count,value);
}
GLAPI void APIENTRY glUniform2uiv(GLint location, GLsizei count, const GLuint* value)
{
  assert(pfn_glUniform2uiv);
  pfn_glUniform2uiv(location,count,value);
}
GLAPI void APIENTRY glUniform3uiv(GLint location, GLsizei count, const GLuint* value)
{
  assert(pfn_glUniform3uiv);
  pfn_glUniform3uiv(location,count,value);
}
GLAPI void APIENTRY glUniform4uiv(GLint location, GLsizei count, const GLuint* value)
{
  assert(pfn_glUniform4uiv);
  pfn_glUniform4uiv(location,count,value);
}
GLAPI void APIENTRY glTexParameterIiv(GLenum target, GLenum pname, const GLint* params)
{
  assert(pfn_glTexParameterIiv);
  pfn_glTexParameterIiv(target,pname,params);
}
GLAPI void APIENTRY glTexParameterIuiv(GLenum target, GLenum pname, const GLuint* params)
{
  assert(pfn_glTexParameterIuiv);
  pfn_glTexParameterIuiv(target,pname,params);
}
GLAPI void APIENTRY glGetTexParameterIiv(GLenum target, GLenum pname, GLint* params)
{
  assert(pfn_glGetTexParameterIiv);
  pfn_glGetTexParameterIiv(target,pname,params);
}
GLAPI void APIENTRY glGetTexParameterIuiv(GLenum target, GLenum pname, GLuint* params)
{
  assert(pfn_glGetTexParameterIuiv);
  pfn_glGetTexParameterIuiv(target,pname,params);
}
GLAPI void APIENTRY glClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint* value)
{
  assert(pfn_glClearBufferiv);
  pfn_glClearBufferiv(buffer,drawbuffer,value);
}
GLAPI void APIENTRY glClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint* value)
{
  assert(pfn_glClearBufferuiv);
  pfn_glClearBufferuiv(buffer,drawbuffer,value);
}
GLAPI void APIENTRY glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat* value)
{
  assert(pfn_glClearBufferfv);
  pfn_glClearBufferfv(buffer,drawbuffer,value);
}
GLAPI void APIENTRY glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)
{
  assert(pfn_glClearBufferfi);
  pfn_glClearBufferfi(buffer,drawbuffer,depth,stencil);
}
GLAPI const GLubyte* APIENTRY glGetStringi(GLenum name, GLuint index)
{
  assert(pfn_glGetStringi);
  return pfn_glGetStringi(name,index);
}
GLAPI GLboolean APIENTRY glIsRenderbuffer(GLuint renderbuffer)
{
  assert(pfn_glIsRenderbuffer);
  return pfn_glIsRenderbuffer(renderbuffer);
}
GLAPI void APIENTRY glBindRenderbuffer(GLenum target, GLuint renderbuffer)
{
  assert(pfn_glBindRenderbuffer);
  pfn_glBindRenderbuffer(target,renderbuffer);
}
GLAPI void APIENTRY glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers)
{
  assert(pfn_glDeleteRenderbuffers);
  pfn_glDeleteRenderbuffers(n,renderbuffers);
}
GLAPI void APIENTRY glGenRenderbuffers(GLsizei n, GLuint* renderbuffers)
{
  assert(pfn_glGenRenderbuffers);
  pfn_glGenRenderbuffers(n,renderbuffers);
}
GLAPI void APIENTRY glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
  assert(pfn_glRenderbufferStorage);
  pfn_glRenderbufferStorage(target,internalformat,width,height);
}
GLAPI void APIENTRY glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params)
{
  assert(pfn_glGetRenderbufferParameteriv);
  pfn_glGetRenderbufferParameteriv(target,pname,params);
}
GLAPI GLboolean APIENTRY glIsFramebuffer(GLuint framebuffer)
{
  assert(pfn_glIsFramebuffer);
  return pfn_glIsFramebuffer(framebuffer);
}
GLAPI void APIENTRY glBindFramebuffer(GLenum target, GLuint framebuffer)
{
  assert(pfn_glBindFramebuffer);
  pfn_glBindFramebuffer(target,framebuffer);
}
GLAPI void APIENTRY glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers)
{
  assert(pfn_glDeleteFramebuffers);
  pfn_glDeleteFramebuffers(n,framebuffers);
}
GLAPI void APIENTRY glGenFramebuffers(GLsizei n, GLuint* framebuffers)
{
  assert(pfn_glGenFramebuffers);
  pfn_glGenFramebuffers(n,framebuffers);
}
GLAPI GLenum APIENTRY glCheckFramebufferStatus(GLenum target)
{
  assert(pfn_glCheckFramebufferStatus);
  return pfn_glCheckFramebufferStatus(target);
}
GLAPI void APIENTRY glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
  assert(pfn_glFramebufferTexture1D);
  pfn_glFramebufferTexture1D(target,attachment,textarget,texture,level);
}
GLAPI void APIENTRY glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
  assert(pfn_glFramebufferTexture2D);
  pfn_glFramebufferTexture2D(target,attachment,textarget,texture,level);
}
GLAPI void APIENTRY glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset)
{
  assert(pfn_glFramebufferTexture3D);
  pfn_glFramebufferTexture3D(target,attachment,textarget,texture,level,zoffset);
}
GLAPI void APIENTRY glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
  assert(pfn_glFramebufferRenderbuffer);
  pfn_glFramebufferRenderbuffer(target,attachment,renderbuffertarget,renderbuffer);
}
GLAPI void APIENTRY glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params)
{
  assert(pfn_glGetFramebufferAttachmentParameteriv);
  pfn_glGetFramebufferAttachmentParameteriv(target,attachment,pname,params);
}
GLAPI void APIENTRY glGenerateMipmap(GLenum target)
{
  assert(pfn_glGenerateMipmap);
  pfn_glGenerateMipmap(target);
}
GLAPI void APIENTRY glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
{
  assert(pfn_glBlitFramebuffer);
  pfn_glBlitFramebuffer(srcX0,srcY0,srcX1,srcY1,dstX0,dstY0,dstX1,dstY1,mask,filter);
}
GLAPI void APIENTRY glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
  assert(pfn_glRenderbufferStorageMultisample);
  pfn_glRenderbufferStorageMultisample(target,samples,internalformat,width,height);
}
GLAPI void APIENTRY glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer)
{
  assert(pfn_glFramebufferTextureLayer);
  pfn_glFramebufferTextureLayer(target,attachment,texture,level,layer);
}
GLAPI void* APIENTRY glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)
{
  assert(pfn_glMapBufferRange);
  return pfn_glMapBufferRange(target,offset,length,access);
}
GLAPI void APIENTRY glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length)
{
  assert(pfn_glFlushMappedBufferRange);
  pfn_glFlushMappedBufferRange(target,offset,length);
}
GLAPI void APIENTRY glBindVertexArray(GLuint array)
{
  assert(pfn_glBindVertexArray);
  pfn_glBindVertexArray(array);
}
GLAPI void APIENTRY glDeleteVertexArrays(GLsizei n, const GLuint* arrays)
{
  assert(pfn_glDeleteVertexArrays);
  pfn_glDeleteVertexArrays(n,arrays);
}
GLAPI void APIENTRY glGenVertexArrays(GLsizei n, GLuint* arrays)
{
  assert(pfn_glGenVertexArrays);
  pfn_glGenVertexArrays(n,arrays);
}
GLAPI GLboolean APIENTRY glIsVertexArray(GLuint array)
{
  assert(pfn_glIsVertexArray);
  return pfn_glIsVertexArray(array);
}

int load_GL_VERSION_3_0(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glColorMaski = (PFNGLCOLORMASKIPROC)fnGetProcAddress("glColorMaski");
  pfn_glGetBooleani_v = (PFNGLGETBOOLEANI_VPROC)fnGetProcAddress("glGetBooleani_v");
  pfn_glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC)fnGetProcAddress("glGetIntegeri_v");
  pfn_glEnablei = (PFNGLENABLEIPROC)fnGetProcAddress("glEnablei");
  pfn_glDisablei = (PFNGLDISABLEIPROC)fnGetProcAddress("glDisablei");
  pfn_glIsEnabledi = (PFNGLISENABLEDIPROC)fnGetProcAddress("glIsEnabledi");
  pfn_glBeginTransformFeedback = (PFNGLBEGINTRANSFORMFEEDBACKPROC)fnGetProcAddress("glBeginTransformFeedback");
  pfn_glEndTransformFeedback = (PFNGLENDTRANSFORMFEEDBACKPROC)fnGetProcAddress("glEndTransformFeedback");
  pfn_glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC)fnGetProcAddress("glBindBufferRange");
  pfn_glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)fnGetProcAddress("glBindBufferBase");
  pfn_glTransformFeedbackVaryings = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC)fnGetProcAddress("glTransformFeedbackVaryings");
  pfn_glGetTransformFeedbackVarying = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)fnGetProcAddress("glGetTransformFeedbackVarying");
  pfn_glClampColor = (PFNGLCLAMPCOLORPROC)fnGetProcAddress("glClampColor");
  pfn_glBeginConditionalRender = (PFNGLBEGINCONDITIONALRENDERPROC)fnGetProcAddress("glBeginConditionalRender");
  pfn_glEndConditionalRender = (PFNGLENDCONDITIONALRENDERPROC)fnGetProcAddress("glEndConditionalRender");
  pfn_glVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC)fnGetProcAddress("glVertexAttribIPointer");
  pfn_glGetVertexAttribIiv = (PFNGLGETVERTEXATTRIBIIVPROC)fnGetProcAddress("glGetVertexAttribIiv");
  pfn_glGetVertexAttribIuiv = (PFNGLGETVERTEXATTRIBIUIVPROC)fnGetProcAddress("glGetVertexAttribIuiv");
  pfn_glVertexAttribI1i = (PFNGLVERTEXATTRIBI1IPROC)fnGetProcAddress("glVertexAttribI1i");
  pfn_glVertexAttribI2i = (PFNGLVERTEXATTRIBI2IPROC)fnGetProcAddress("glVertexAttribI2i");
  pfn_glVertexAttribI3i = (PFNGLVERTEXATTRIBI3IPROC)fnGetProcAddress("glVertexAttribI3i");
  pfn_glVertexAttribI4i = (PFNGLVERTEXATTRIBI4IPROC)fnGetProcAddress("glVertexAttribI4i");
  pfn_glVertexAttribI1ui = (PFNGLVERTEXATTRIBI1UIPROC)fnGetProcAddress("glVertexAttribI1ui");
  pfn_glVertexAttribI2ui = (PFNGLVERTEXATTRIBI2UIPROC)fnGetProcAddress("glVertexAttribI2ui");
  pfn_glVertexAttribI3ui = (PFNGLVERTEXATTRIBI3UIPROC)fnGetProcAddress("glVertexAttribI3ui");
  pfn_glVertexAttribI4ui = (PFNGLVERTEXATTRIBI4UIPROC)fnGetProcAddress("glVertexAttribI4ui");
  pfn_glVertexAttribI1iv = (PFNGLVERTEXATTRIBI1IVPROC)fnGetProcAddress("glVertexAttribI1iv");
  pfn_glVertexAttribI2iv = (PFNGLVERTEXATTRIBI2IVPROC)fnGetProcAddress("glVertexAttribI2iv");
  pfn_glVertexAttribI3iv = (PFNGLVERTEXATTRIBI3IVPROC)fnGetProcAddress("glVertexAttribI3iv");
  pfn_glVertexAttribI4iv = (PFNGLVERTEXATTRIBI4IVPROC)fnGetProcAddress("glVertexAttribI4iv");
  pfn_glVertexAttribI1uiv = (PFNGLVERTEXATTRIBI1UIVPROC)fnGetProcAddress("glVertexAttribI1uiv");
  pfn_glVertexAttribI2uiv = (PFNGLVERTEXATTRIBI2UIVPROC)fnGetProcAddress("glVertexAttribI2uiv");
  pfn_glVertexAttribI3uiv = (PFNGLVERTEXATTRIBI3UIVPROC)fnGetProcAddress("glVertexAttribI3uiv");
  pfn_glVertexAttribI4uiv = (PFNGLVERTEXATTRIBI4UIVPROC)fnGetProcAddress("glVertexAttribI4uiv");
  pfn_glVertexAttribI4bv = (PFNGLVERTEXATTRIBI4BVPROC)fnGetProcAddress("glVertexAttribI4bv");
  pfn_glVertexAttribI4sv = (PFNGLVERTEXATTRIBI4SVPROC)fnGetProcAddress("glVertexAttribI4sv");
  pfn_glVertexAttribI4ubv = (PFNGLVERTEXATTRIBI4UBVPROC)fnGetProcAddress("glVertexAttribI4ubv");
  pfn_glVertexAttribI4usv = (PFNGLVERTEXATTRIBI4USVPROC)fnGetProcAddress("glVertexAttribI4usv");
  pfn_glGetUniformuiv = (PFNGLGETUNIFORMUIVPROC)fnGetProcAddress("glGetUniformuiv");
  pfn_glBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC)fnGetProcAddress("glBindFragDataLocation");
  pfn_glGetFragDataLocation = (PFNGLGETFRAGDATALOCATIONPROC)fnGetProcAddress("glGetFragDataLocation");
  pfn_glUniform1ui = (PFNGLUNIFORM1UIPROC)fnGetProcAddress("glUniform1ui");
  pfn_glUniform2ui = (PFNGLUNIFORM2UIPROC)fnGetProcAddress("glUniform2ui");
  pfn_glUniform3ui = (PFNGLUNIFORM3UIPROC)fnGetProcAddress("glUniform3ui");
  pfn_glUniform4ui = (PFNGLUNIFORM4UIPROC)fnGetProcAddress("glUniform4ui");
  pfn_glUniform1uiv = (PFNGLUNIFORM1UIVPROC)fnGetProcAddress("glUniform1uiv");
  pfn_glUniform2uiv = (PFNGLUNIFORM2UIVPROC)fnGetProcAddress("glUniform2uiv");
  pfn_glUniform3uiv = (PFNGLUNIFORM3UIVPROC)fnGetProcAddress("glUniform3uiv");
  pfn_glUniform4uiv = (PFNGLUNIFORM4UIVPROC)fnGetProcAddress("glUniform4uiv");
  pfn_glTexParameterIiv = (PFNGLTEXPARAMETERIIVPROC)fnGetProcAddress("glTexParameterIiv");
  pfn_glTexParameterIuiv = (PFNGLTEXPARAMETERIUIVPROC)fnGetProcAddress("glTexParameterIuiv");
  pfn_glGetTexParameterIiv = (PFNGLGETTEXPARAMETERIIVPROC)fnGetProcAddress("glGetTexParameterIiv");
  pfn_glGetTexParameterIuiv = (PFNGLGETTEXPARAMETERIUIVPROC)fnGetProcAddress("glGetTexParameterIuiv");
  pfn_glClearBufferiv = (PFNGLCLEARBUFFERIVPROC)fnGetProcAddress("glClearBufferiv");
  pfn_glClearBufferuiv = (PFNGLCLEARBUFFERUIVPROC)fnGetProcAddress("glClearBufferuiv");
  pfn_glClearBufferfv = (PFNGLCLEARBUFFERFVPROC)fnGetProcAddress("glClearBufferfv");
  pfn_glClearBufferfi = (PFNGLCLEARBUFFERFIPROC)fnGetProcAddress("glClearBufferfi");
  pfn_glGetStringi = (PFNGLGETSTRINGIPROC)fnGetProcAddress("glGetStringi");
  pfn_glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)fnGetProcAddress("glIsRenderbuffer");
  pfn_glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)fnGetProcAddress("glBindRenderbuffer");
  pfn_glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)fnGetProcAddress("glDeleteRenderbuffers");
  pfn_glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)fnGetProcAddress("glGenRenderbuffers");
  pfn_glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)fnGetProcAddress("glRenderbufferStorage");
  pfn_glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)fnGetProcAddress("glGetRenderbufferParameteriv");
  pfn_glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)fnGetProcAddress("glIsFramebuffer");
  pfn_glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)fnGetProcAddress("glBindFramebuffer");
  pfn_glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)fnGetProcAddress("glDeleteFramebuffers");
  pfn_glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)fnGetProcAddress("glGenFramebuffers");
  pfn_glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)fnGetProcAddress("glCheckFramebufferStatus");
  pfn_glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC)fnGetProcAddress("glFramebufferTexture1D");
  pfn_glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)fnGetProcAddress("glFramebufferTexture2D");
  pfn_glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC)fnGetProcAddress("glFramebufferTexture3D");
  pfn_glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)fnGetProcAddress("glFramebufferRenderbuffer");
  pfn_glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)fnGetProcAddress("glGetFramebufferAttachmentParameteriv");
  pfn_glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)fnGetProcAddress("glGenerateMipmap");
  pfn_glBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC)fnGetProcAddress("glBlitFramebuffer");
  pfn_glRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)fnGetProcAddress("glRenderbufferStorageMultisample");
  pfn_glFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC)fnGetProcAddress("glFramebufferTextureLayer");
  pfn_glMapBufferRange = (PFNGLMAPBUFFERRANGEPROC)fnGetProcAddress("glMapBufferRange");
  pfn_glFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC)fnGetProcAddress("glFlushMappedBufferRange");
  pfn_glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)fnGetProcAddress("glBindVertexArray");
  pfn_glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)fnGetProcAddress("glDeleteVertexArrays");
  pfn_glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)fnGetProcAddress("glGenVertexArrays");
  pfn_glIsVertexArray = (PFNGLISVERTEXARRAYPROC)fnGetProcAddress("glIsVertexArray");
  int success = has_version(3,0);
  success = success && (pfn_glColorMaski != 0);
  success = success && (pfn_glGetBooleani_v != 0);
  success = success && (pfn_glGetIntegeri_v != 0);
  success = success && (pfn_glEnablei != 0);
  success = success && (pfn_glDisablei != 0);
  success = success && (pfn_glIsEnabledi != 0);
  success = success && (pfn_glBeginTransformFeedback != 0);
  success = success && (pfn_glEndTransformFeedback != 0);
  success = success && (pfn_glBindBufferRange != 0);
  success = success && (pfn_glBindBufferBase != 0);
  success = success && (pfn_glTransformFeedbackVaryings != 0);
  success = success && (pfn_glGetTransformFeedbackVarying != 0);
  success = success && (pfn_glClampColor != 0);
  success = success && (pfn_glBeginConditionalRender != 0);
  success = success && (pfn_glEndConditionalRender != 0);
  success = success && (pfn_glVertexAttribIPointer != 0);
  success = success && (pfn_glGetVertexAttribIiv != 0);
  success = success && (pfn_glGetVertexAttribIuiv != 0);
  success = success && (pfn_glVertexAttribI1i != 0);
  success = success && (pfn_glVertexAttribI2i != 0);
  success = success && (pfn_glVertexAttribI3i != 0);
  success = success && (pfn_glVertexAttribI4i != 0);
  success = success && (pfn_glVertexAttribI1ui != 0);
  success = success && (pfn_glVertexAttribI2ui != 0);
  success = success && (pfn_glVertexAttribI3ui != 0);
  success = success && (pfn_glVertexAttribI4ui != 0);
  success = success && (pfn_glVertexAttribI1iv != 0);
  success = success && (pfn_glVertexAttribI2iv != 0);
  success = success && (pfn_glVertexAttribI3iv != 0);
  success = success && (pfn_glVertexAttribI4iv != 0);
  success = success && (pfn_glVertexAttribI1uiv != 0);
  success = success && (pfn_glVertexAttribI2uiv != 0);
  success = success && (pfn_glVertexAttribI3uiv != 0);
  success = success && (pfn_glVertexAttribI4uiv != 0);
  success = success && (pfn_glVertexAttribI4bv != 0);
  success = success && (pfn_glVertexAttribI4sv != 0);
  success = success && (pfn_glVertexAttribI4ubv != 0);
  success = success && (pfn_glVertexAttribI4usv != 0);
  success = success && (pfn_glGetUniformuiv != 0);
  success = success && (pfn_glBindFragDataLocation != 0);
  success = success && (pfn_glGetFragDataLocation != 0);
  success = success && (pfn_glUniform1ui != 0);
  success = success && (pfn_glUniform2ui != 0);
  success = success && (pfn_glUniform3ui != 0);
  success = success && (pfn_glUniform4ui != 0);
  success = success && (pfn_glUniform1uiv != 0);
  success = success && (pfn_glUniform2uiv != 0);
  success = success && (pfn_glUniform3uiv != 0);
  success = success && (pfn_glUniform4uiv != 0);
  success = success && (pfn_glTexParameterIiv != 0);
  success = success && (pfn_glTexParameterIuiv != 0);
  success = success && (pfn_glGetTexParameterIiv != 0);
  success = success && (pfn_glGetTexParameterIuiv != 0);
  success = success && (pfn_glClearBufferiv != 0);
  success = success && (pfn_glClearBufferuiv != 0);
  success = success && (pfn_glClearBufferfv != 0);
  success = success && (pfn_glClearBufferfi != 0);
  success = success && (pfn_glGetStringi != 0);
  success = success && (pfn_glIsRenderbuffer != 0);
  success = success && (pfn_glBindRenderbuffer != 0);
  success = success && (pfn_glDeleteRenderbuffers != 0);
  success = success && (pfn_glGenRenderbuffers != 0);
  success = success && (pfn_glRenderbufferStorage != 0);
  success = success && (pfn_glGetRenderbufferParameteriv != 0);
  success = success && (pfn_glIsFramebuffer != 0);
  success = success && (pfn_glBindFramebuffer != 0);
  success = success && (pfn_glDeleteFramebuffers != 0);
  success = success && (pfn_glGenFramebuffers != 0);
  success = success && (pfn_glCheckFramebufferStatus != 0);
  success = success && (pfn_glFramebufferTexture1D != 0);
  success = success && (pfn_glFramebufferTexture2D != 0);
  success = success && (pfn_glFramebufferTexture3D != 0);
  success = success && (pfn_glFramebufferRenderbuffer != 0);
  success = success && (pfn_glGetFramebufferAttachmentParameteriv != 0);
  success = success && (pfn_glGenerateMipmap != 0);
  success = success && (pfn_glBlitFramebuffer != 0);
  success = success && (pfn_glRenderbufferStorageMultisample != 0);
  success = success && (pfn_glFramebufferTextureLayer != 0);
  success = success && (pfn_glMapBufferRange != 0);
  success = success && (pfn_glFlushMappedBufferRange != 0);
  success = success && (pfn_glBindVertexArray != 0);
  success = success && (pfn_glDeleteVertexArrays != 0);
  success = success && (pfn_glGenVertexArrays != 0);
  success = success && (pfn_glIsVertexArray != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_VERSION_3_1 */

static PFNGLDRAWARRAYSINSTANCEDPROC pfn_glDrawArraysInstanced = 0;
static PFNGLDRAWELEMENTSINSTANCEDPROC pfn_glDrawElementsInstanced = 0;
static PFNGLTEXBUFFERPROC pfn_glTexBuffer = 0;
static PFNGLPRIMITIVERESTARTINDEXPROC pfn_glPrimitiveRestartIndex = 0;
static PFNGLCOPYBUFFERSUBDATAPROC pfn_glCopyBufferSubData = 0;
static PFNGLGETUNIFORMINDICESPROC pfn_glGetUniformIndices = 0;
static PFNGLGETACTIVEUNIFORMSIVPROC pfn_glGetActiveUniformsiv = 0;
static PFNGLGETACTIVEUNIFORMNAMEPROC pfn_glGetActiveUniformName = 0;
static PFNGLGETUNIFORMBLOCKINDEXPROC pfn_glGetUniformBlockIndex = 0;
static PFNGLGETACTIVEUNIFORMBLOCKIVPROC pfn_glGetActiveUniformBlockiv = 0;
static PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC pfn_glGetActiveUniformBlockName = 0;
static PFNGLUNIFORMBLOCKBINDINGPROC pfn_glUniformBlockBinding = 0;

GLAPI void APIENTRY glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount)
{
  assert(pfn_glDrawArraysInstanced);
  pfn_glDrawArraysInstanced(mode,first,count,instancecount);
}
GLAPI void APIENTRY glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount)
{
  assert(pfn_glDrawElementsInstanced);
  pfn_glDrawElementsInstanced(mode,count,type,indices,instancecount);
}
GLAPI void APIENTRY glTexBuffer(GLenum target, GLenum internalformat, GLuint buffer)
{
  assert(pfn_glTexBuffer);
  pfn_glTexBuffer(target,internalformat,buffer);
}
GLAPI void APIENTRY glPrimitiveRestartIndex(GLuint index)
{
  assert(pfn_glPrimitiveRestartIndex);
  pfn_glPrimitiveRestartIndex(index);
}
GLAPI void APIENTRY glCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
{
  assert(pfn_glCopyBufferSubData);
  pfn_glCopyBufferSubData(readTarget,writeTarget,readOffset,writeOffset,size);
}
GLAPI void APIENTRY glGetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar* const* uniformNames, GLuint* uniformIndices)
{
  assert(pfn_glGetUniformIndices);
  pfn_glGetUniformIndices(program,uniformCount,uniformNames,uniformIndices);
}
GLAPI void APIENTRY glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname, GLint* params)
{
  assert(pfn_glGetActiveUniformsiv);
  pfn_glGetActiveUniformsiv(program,uniformCount,uniformIndices,pname,params);
}
GLAPI void APIENTRY glGetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformName)
{
  assert(pfn_glGetActiveUniformName);
  pfn_glGetActiveUniformName(program,uniformIndex,bufSize,length,uniformName);
}
GLAPI GLuint APIENTRY glGetUniformBlockIndex(GLuint program, const GLchar* uniformBlockName)
{
  assert(pfn_glGetUniformBlockIndex);
  return pfn_glGetUniformBlockIndex(program,uniformBlockName);
}
GLAPI void APIENTRY glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params)
{
  assert(pfn_glGetActiveUniformBlockiv);
  pfn_glGetActiveUniformBlockiv(program,uniformBlockIndex,pname,params);
}
GLAPI void APIENTRY glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName)
{
  assert(pfn_glGetActiveUniformBlockName);
  pfn_glGetActiveUniformBlockName(program,uniformBlockIndex,bufSize,length,uniformBlockName);
}
GLAPI void APIENTRY glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)
{
  assert(pfn_glUniformBlockBinding);
  pfn_glUniformBlockBinding(program,uniformBlockIndex,uniformBlockBinding);
}

int load_GL_VERSION_3_1(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC)fnGetProcAddress("glDrawArraysInstanced");
  pfn_glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC)fnGetProcAddress("glDrawElementsInstanced");
  pfn_glTexBuffer = (PFNGLTEXBUFFERPROC)fnGetProcAddress("glTexBuffer");
  pfn_glPrimitiveRestartIndex = (PFNGLPRIMITIVERESTARTINDEXPROC)fnGetProcAddress("glPrimitiveRestartIndex");
  pfn_glCopyBufferSubData = (PFNGLCOPYBUFFERSUBDATAPROC)fnGetProcAddress("glCopyBufferSubData");
  pfn_glGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC)fnGetProcAddress("glGetUniformIndices");
  pfn_glGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC)fnGetProcAddress("glGetActiveUniformsiv");
  pfn_glGetActiveUniformName = (PFNGLGETACTIVEUNIFORMNAMEPROC)fnGetProcAddress("glGetActiveUniformName");
  pfn_glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC)fnGetProcAddress("glGetUniformBlockIndex");
  pfn_glGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)fnGetProcAddress("glGetActiveUniformBlockiv");
  pfn_glGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)fnGetProcAddress("glGetActiveUniformBlockName");
  pfn_glUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC)fnGetProcAddress("glUniformBlockBinding");
  int success = has_version(3,1);
  success = success && (pfn_glDrawArraysInstanced != 0);
  success = success && (pfn_glDrawElementsInstanced != 0);
  success = success && (pfn_glTexBuffer != 0);
  success = success && (pfn_glPrimitiveRestartIndex != 0);
  success = success && (pfn_glCopyBufferSubData != 0);
  success = success && (pfn_glGetUniformIndices != 0);
  success = success && (pfn_glGetActiveUniformsiv != 0);
  success = success && (pfn_glGetActiveUniformName != 0);
  success = success && (pfn_glGetUniformBlockIndex != 0);
  success = success && (pfn_glGetActiveUniformBlockiv != 0);
  success = success && (pfn_glGetActiveUniformBlockName != 0);
  success = success && (pfn_glUniformBlockBinding != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_VERSION_3_2 */

static PFNGLDRAWELEMENTSBASEVERTEXPROC pfn_glDrawElementsBaseVertex = 0;
static PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC pfn_glDrawRangeElementsBaseVertex = 0;
static PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC pfn_glDrawElementsInstancedBaseVertex = 0;
static PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC pfn_glMultiDrawElementsBaseVertex = 0;
static PFNGLPROVOKINGVERTEXPROC pfn_glProvokingVertex = 0;
static PFNGLFENCESYNCPROC pfn_glFenceSync = 0;
static PFNGLISSYNCPROC pfn_glIsSync = 0;
static PFNGLDELETESYNCPROC pfn_glDeleteSync = 0;
static PFNGLCLIENTWAITSYNCPROC pfn_glClientWaitSync = 0;
static PFNGLWAITSYNCPROC pfn_glWaitSync = 0;
static PFNGLGETINTEGER64VPROC pfn_glGetInteger64v = 0;
static PFNGLGETSYNCIVPROC pfn_glGetSynciv = 0;
static PFNGLGETINTEGER64I_VPROC pfn_glGetInteger64i_v = 0;
static PFNGLGETBUFFERPARAMETERI64VPROC pfn_glGetBufferParameteri64v = 0;
static PFNGLFRAMEBUFFERTEXTUREPROC pfn_glFramebufferTexture = 0;
static PFNGLTEXIMAGE2DMULTISAMPLEPROC pfn_glTexImage2DMultisample = 0;
static PFNGLTEXIMAGE3DMULTISAMPLEPROC pfn_glTexImage3DMultisample = 0;
static PFNGLGETMULTISAMPLEFVPROC pfn_glGetMultisamplefv = 0;
static PFNGLSAMPLEMASKIPROC pfn_glSampleMaski = 0;

GLAPI void APIENTRY glDrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const void* indices, GLint basevertex)
{
  assert(pfn_glDrawElementsBaseVertex);
  pfn_glDrawElementsBaseVertex(mode,count,type,indices,basevertex);
}
GLAPI void APIENTRY glDrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices, GLint basevertex)
{
  assert(pfn_glDrawRangeElementsBaseVertex);
  pfn_glDrawRangeElementsBaseVertex(mode,start,end,count,type,indices,basevertex);
}
GLAPI void APIENTRY glDrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount, GLint basevertex)
{
  assert(pfn_glDrawElementsInstancedBaseVertex);
  pfn_glDrawElementsInstancedBaseVertex(mode,count,type,indices,instancecount,basevertex);
}
GLAPI void APIENTRY glMultiDrawElementsBaseVertex(GLenum mode, const GLsizei* count, GLenum type, const void* const* indices, GLsizei drawcount, const GLint* basevertex)
{
  assert(pfn_glMultiDrawElementsBaseVertex);
  pfn_glMultiDrawElementsBaseVertex(mode,count,type,indices,drawcount,basevertex);
}
GLAPI void APIENTRY glProvokingVertex(GLenum mode)
{
  assert(pfn_glProvokingVertex);
  pfn_glProvokingVertex(mode);
}
GLAPI GLsync APIENTRY glFenceSync(GLenum condition, GLbitfield flags)
{
  assert(pfn_glFenceSync);
  return pfn_glFenceSync(condition,flags);
}
GLAPI GLboolean APIENTRY glIsSync(GLsync sync)
{
  assert(pfn_glIsSync);
  return pfn_glIsSync(sync);
}
GLAPI void APIENTRY glDeleteSync(GLsync sync)
{
  assert(pfn_glDeleteSync);
  pfn_glDeleteSync(sync);
}
GLAPI GLenum APIENTRY glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
  assert(pfn_glClientWaitSync);
  return pfn_glClientWaitSync(sync,flags,timeout);
}
GLAPI void APIENTRY glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
  assert(pfn_glWaitSync);
  pfn_glWaitSync(sync,flags,timeout);
}
GLAPI void APIENTRY glGetInteger64v(GLenum pname, GLint64* data)
{
  assert(pfn_glGetInteger64v);
  pfn_glGetInteger64v(pname,data);
}
GLAPI void APIENTRY glGetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values)
{
  assert(pfn_glGetSynciv);
  pfn_glGetSynciv(sync,pname,bufSize,length,values);
}
GLAPI void APIENTRY glGetInteger64i_v(GLenum target, GLuint index, GLint64* data)
{
  assert(pfn_glGetInteger64i_v);
  pfn_glGetInteger64i_v(target,index,data);
}
GLAPI void APIENTRY glGetBufferParameteri64v(GLenum target, GLenum pname, GLint64* params)
{
  assert(pfn_glGetBufferParameteri64v);
  pfn_glGetBufferParameteri64v(target,pname,params);
}
GLAPI void APIENTRY glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level)
{
  assert(pfn_glFramebufferTexture);
  pfn_glFramebufferTexture(target,attachment,texture,level);
}
GLAPI void APIENTRY glTexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
  assert(pfn_glTexImage2DMultisample);
  pfn_glTexImage2DMultisample(target,samples,internalformat,width,height,fixedsamplelocations);
}
GLAPI void APIENTRY glTexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
  assert(pfn_glTexImage3DMultisample);
  pfn_glTexImage3DMultisample(target,samples,internalformat,width,height,depth,fixedsamplelocations);
}
GLAPI void APIENTRY glGetMultisamplefv(GLenum pname, GLuint index, GLfloat* val)
{
  assert(pfn_glGetMultisamplefv);
  pfn_glGetMultisamplefv(pname,index,val);
}
GLAPI void APIENTRY glSampleMaski(GLuint maskNumber, GLbitfield mask)
{
  assert(pfn_glSampleMaski);
  pfn_glSampleMaski(maskNumber,mask);
}

int load_GL_VERSION_3_2(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC)fnGetProcAddress("glDrawElementsBaseVertex");
  pfn_glDrawRangeElementsBaseVertex = (PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)fnGetProcAddress("glDrawRangeElementsBaseVertex");
  pfn_glDrawElementsInstancedBaseVertex = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)fnGetProcAddress("glDrawElementsInstancedBaseVertex");
  pfn_glMultiDrawElementsBaseVertex = (PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)fnGetProcAddress("glMultiDrawElementsBaseVertex");
  pfn_glProvokingVertex = (PFNGLPROVOKINGVERTEXPROC)fnGetProcAddress("glProvokingVertex");
  pfn_glFenceSync = (PFNGLFENCESYNCPROC)fnGetProcAddress("glFenceSync");
  pfn_glIsSync = (PFNGLISSYNCPROC)fnGetProcAddress("glIsSync");
  pfn_glDeleteSync = (PFNGLDELETESYNCPROC)fnGetProcAddress("glDeleteSync");
  pfn_glClientWaitSync = (PFNGLCLIENTWAITSYNCPROC)fnGetProcAddress("glClientWaitSync");
  pfn_glWaitSync = (PFNGLWAITSYNCPROC)fnGetProcAddress("glWaitSync");
  pfn_glGetInteger64v = (PFNGLGETINTEGER64VPROC)fnGetProcAddress("glGetInteger64v");
  pfn_glGetSynciv = (PFNGLGETSYNCIVPROC)fnGetProcAddress("glGetSynciv");
  pfn_glGetInteger64i_v = (PFNGLGETINTEGER64I_VPROC)fnGetProcAddress("glGetInteger64i_v");
  pfn_glGetBufferParameteri64v = (PFNGLGETBUFFERPARAMETERI64VPROC)fnGetProcAddress("glGetBufferParameteri64v");
  pfn_glFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREPROC)fnGetProcAddress("glFramebufferTexture");
  pfn_glTexImage2DMultisample = (PFNGLTEXIMAGE2DMULTISAMPLEPROC)fnGetProcAddress("glTexImage2DMultisample");
  pfn_glTexImage3DMultisample = (PFNGLTEXIMAGE3DMULTISAMPLEPROC)fnGetProcAddress("glTexImage3DMultisample");
  pfn_glGetMultisamplefv = (PFNGLGETMULTISAMPLEFVPROC)fnGetProcAddress("glGetMultisamplefv");
  pfn_glSampleMaski = (PFNGLSAMPLEMASKIPROC)fnGetProcAddress("glSampleMaski");
  int success = has_version(3,2);
  success = success && (pfn_glDrawElementsBaseVertex != 0);
  success = success && (pfn_glDrawRangeElementsBaseVertex != 0);
  success = success && (pfn_glDrawElementsInstancedBaseVertex != 0);
  success = success && (pfn_glMultiDrawElementsBaseVertex != 0);
  success = success && (pfn_glProvokingVertex != 0);
  success = success && (pfn_glFenceSync != 0);
  success = success && (pfn_glIsSync != 0);
  success = success && (pfn_glDeleteSync != 0);
  success = success && (pfn_glClientWaitSync != 0);
  success = success && (pfn_glWaitSync != 0);
  success = success && (pfn_glGetInteger64v != 0);
  success = success && (pfn_glGetSynciv != 0);
  success = success && (pfn_glGetInteger64i_v != 0);
  success = success && (pfn_glGetBufferParameteri64v != 0);
  success = success && (pfn_glFramebufferTexture != 0);
  success = success && (pfn_glTexImage2DMultisample != 0);
  success = success && (pfn_glTexImage3DMultisample != 0);
  success = success && (pfn_glGetMultisamplefv != 0);
  success = success && (pfn_glSampleMaski != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_VERSION_3_3 */

static PFNGLBINDFRAGDATALOCATIONINDEXEDPROC pfn_glBindFragDataLocationIndexed = 0;
static PFNGLGETFRAGDATAINDEXPROC pfn_glGetFragDataIndex = 0;
static PFNGLGENSAMPLERSPROC pfn_glGenSamplers = 0;
static PFNGLDELETESAMPLERSPROC pfn_glDeleteSamplers = 0;
static PFNGLISSAMPLERPROC pfn_glIsSampler = 0;
static PFNGLBINDSAMPLERPROC pfn_glBindSampler = 0;
static PFNGLSAMPLERPARAMETERIPROC pfn_glSamplerParameteri = 0;
static PFNGLSAMPLERPARAMETERIVPROC pfn_glSamplerParameteriv = 0;
static PFNGLSAMPLERPARAMETERFPROC pfn_glSamplerParameterf = 0;
static PFNGLSAMPLERPARAMETERFVPROC pfn_glSamplerParameterfv = 0;
static PFNGLSAMPLERPARAMETERIIVPROC pfn_glSamplerParameterIiv = 0;
static PFNGLSAMPLERPARAMETERIUIVPROC pfn_glSamplerParameterIuiv = 0;
static PFNGLGETSAMPLERPARAMETERIVPROC pfn_glGetSamplerParameteriv = 0;
static PFNGLGETSAMPLERPARAMETERIIVPROC pfn_glGetSamplerParameterIiv = 0;
static PFNGLGETSAMPLERPARAMETERFVPROC pfn_glGetSamplerParameterfv = 0;
static PFNGLGETSAMPLERPARAMETERIUIVPROC pfn_glGetSamplerParameterIuiv = 0;
static PFNGLQUERYCOUNTERPROC pfn_glQueryCounter = 0;
static PFNGLGETQUERYOBJECTI64VPROC pfn_glGetQueryObjecti64v = 0;
static PFNGLGETQUERYOBJECTUI64VPROC pfn_glGetQueryObjectui64v = 0;
static PFNGLVERTEXATTRIBDIVISORPROC pfn_glVertexAttribDivisor = 0;
static PFNGLVERTEXATTRIBP1UIPROC pfn_glVertexAttribP1ui = 0;
static PFNGLVERTEXATTRIBP1UIVPROC pfn_glVertexAttribP1uiv = 0;
static PFNGLVERTEXATTRIBP2UIPROC pfn_glVertexAttribP2ui = 0;
static PFNGLVERTEXATTRIBP2UIVPROC pfn_glVertexAttribP2uiv = 0;
static PFNGLVERTEXATTRIBP3UIPROC pfn_glVertexAttribP3ui = 0;
static PFNGLVERTEXATTRIBP3UIVPROC pfn_glVertexAttribP3uiv = 0;
static PFNGLVERTEXATTRIBP4UIPROC pfn_glVertexAttribP4ui = 0;
static PFNGLVERTEXATTRIBP4UIVPROC pfn_glVertexAttribP4uiv = 0;

GLAPI void APIENTRY glBindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, const GLchar* name)
{
  assert(pfn_glBindFragDataLocationIndexed);
  pfn_glBindFragDataLocationIndexed(program,colorNumber,index,name);
}
GLAPI GLint APIENTRY glGetFragDataIndex(GLuint program, const GLchar* name)
{
  assert(pfn_glGetFragDataIndex);
  return pfn_glGetFragDataIndex(program,name);
}
GLAPI void APIENTRY glGenSamplers(GLsizei count, GLuint* samplers)
{
  assert(pfn_glGenSamplers);
  pfn_glGenSamplers(count,samplers);
}
GLAPI void APIENTRY glDeleteSamplers(GLsizei count, const GLuint* samplers)
{
  assert(pfn_glDeleteSamplers);
  pfn_glDeleteSamplers(count,samplers);
}
GLAPI GLboolean APIENTRY glIsSampler(GLuint sampler)
{
  assert(pfn_glIsSampler);
  return pfn_glIsSampler(sampler);
}
GLAPI void APIENTRY glBindSampler(GLuint unit, GLuint sampler)
{
  assert(pfn_glBindSampler);
  pfn_glBindSampler(unit,sampler);
}
GLAPI void APIENTRY glSamplerParameteri(GLuint sampler, GLenum pname, GLint param)
{
  assert(pfn_glSamplerParameteri);
  pfn_glSamplerParameteri(sampler,pname,param);
}
GLAPI void APIENTRY glSamplerParameteriv(GLuint sampler, GLenum pname, const GLint* param)
{
  assert(pfn_glSamplerParameteriv);
  pfn_glSamplerParameteriv(sampler,pname,param);
}
GLAPI void APIENTRY glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param)
{
  assert(pfn_glSamplerParameterf);
  pfn_glSamplerParameterf(sampler,pname,param);
}
GLAPI void APIENTRY glSamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat* param)
{
  assert(pfn_glSamplerParameterfv);
  pfn_glSamplerParameterfv(sampler,pname,param);
}
GLAPI void APIENTRY glSamplerParameterIiv(GLuint sampler, GLenum pname, const GLint* param)
{
  assert(pfn_glSamplerParameterIiv);
  pfn_glSamplerParameterIiv(sampler,pname,param);
}
GLAPI void APIENTRY glSamplerParameterIuiv(GLuint sampler, GLenum pname, const GLuint* param)
{
  assert(pfn_glSamplerParameterIuiv);
  pfn_glSamplerParameterIuiv(sampler,pname,param);
}
GLAPI void APIENTRY glGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint* params)
{
  assert(pfn_glGetSamplerParameteriv);
  pfn_glGetSamplerParameteriv(sampler,pname,params);
}
GLAPI void APIENTRY glGetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint* params)
{
  assert(pfn_glGetSamplerParameterIiv);
  pfn_glGetSamplerParameterIiv(sampler,pname,params);
}
GLAPI void APIENTRY glGetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat* params)
{
  assert(pfn_glGetSamplerParameterfv);
  pfn_glGetSamplerParameterfv(sampler,pname,params);
}
GLAPI void APIENTRY glGetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint* params)
{
  assert(pfn_glGetSamplerParameterIuiv);
  pfn_glGetSamplerParameterIuiv(sampler,pname,params);
}
GLAPI void APIENTRY glQueryCounter(GLuint id, GLenum target)
{
  assert(pfn_glQueryCounter);
  pfn_glQueryCounter(id,target);
}
GLAPI void APIENTRY glGetQueryObjecti64v(GLuint id, GLenum pname, GLint64* params)
{
  assert(pfn_glGetQueryObjecti64v);
  pfn_glGetQueryObjecti64v(id,pname,params);
}
GLAPI void APIENTRY glGetQueryObjectui64v(GLuint id, GLenum pname, GLuint64* params)
{
  assert(pfn_glGetQueryObjectui64v);
  pfn_glGetQueryObjectui64v(id,pname,params);
}
GLAPI void APIENTRY glVertexAttribDivisor(GLuint index, GLuint divisor)
{
  assert(pfn_glVertexAttribDivisor);
  pfn_glVertexAttribDivisor(index,divisor);
}
GLAPI void APIENTRY glVertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
  assert(pfn_glVertexAttribP1ui);
  pfn_glVertexAttribP1ui(index,type,normalized,value);
}
GLAPI void APIENTRY glVertexAttribP1uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint* value)
{
  assert(pfn_glVertexAttribP1uiv);
  pfn_glVertexAttribP1uiv(index,type,normalized,value);
}
GLAPI void APIENTRY glVertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
  assert(pfn_glVertexAttribP2ui);
  pfn_glVertexAttribP2ui(index,type,normalized,value);
}
GLAPI void APIENTRY glVertexAttribP2uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint* value)
{
  assert(pfn_glVertexAttribP2uiv);
  pfn_glVertexAttribP2uiv(index,type,normalized,value);
}
GLAPI void APIENTRY glVertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
  assert(pfn_glVertexAttribP3ui);
  pfn_glVertexAttribP3ui(index,type,normalized,value);
}
GLAPI void APIENTRY glVertexAttribP3uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint* value)
{
  assert(pfn_glVertexAttribP3uiv);
  pfn_glVertexAttribP3uiv(index,type,normalized,value);
}
GLAPI void APIENTRY glVertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
  assert(pfn_glVertexAttribP4ui);
  pfn_glVertexAttribP4ui(index,type,normalized,value);
}
GLAPI void APIENTRY glVertexAttribP4uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint* value)
{
  assert(pfn_glVertexAttribP4uiv);
  pfn_glVertexAttribP4uiv(index,type,normalized,value);
}

int load_GL_VERSION_3_3(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glBindFragDataLocationIndexed = (PFNGLBINDFRAGDATALOCATIONINDEXEDPROC)fnGetProcAddress("glBindFragDataLocationIndexed");
  pfn_glGetFragDataIndex = (PFNGLGETFRAGDATAINDEXPROC)fnGetProcAddress("glGetFragDataIndex");
  pfn_glGenSamplers = (PFNGLGENSAMPLERSPROC)fnGetProcAddress("glGenSamplers");
  pfn_glDeleteSamplers = (PFNGLDELETESAMPLERSPROC)fnGetProcAddress("glDeleteSamplers");
  pfn_glIsSampler = (PFNGLISSAMPLERPROC)fnGetProcAddress("glIsSampler");
  pfn_glBindSampler = (PFNGLBINDSAMPLERPROC)fnGetProcAddress("glBindSampler");
  pfn_glSamplerParameteri = (PFNGLSAMPLERPARAMETERIPROC)fnGetProcAddress("glSamplerParameteri");
  pfn_glSamplerParameteriv = (PFNGLSAMPLERPARAMETERIVPROC)fnGetProcAddress("glSamplerParameteriv");
  pfn_glSamplerParameterf = (PFNGLSAMPLERPARAMETERFPROC)fnGetProcAddress("glSamplerParameterf");
  pfn_glSamplerParameterfv = (PFNGLSAMPLERPARAMETERFVPROC)fnGetProcAddress("glSamplerParameterfv");
  pfn_glSamplerParameterIiv = (PFNGLSAMPLERPARAMETERIIVPROC)fnGetProcAddress("glSamplerParameterIiv");
  pfn_glSamplerParameterIuiv = (PFNGLSAMPLERPARAMETERIUIVPROC)fnGetProcAddress("glSamplerParameterIuiv");
  pfn_glGetSamplerParameteriv = (PFNGLGETSAMPLERPARAMETERIVPROC)fnGetProcAddress("glGetSamplerParameteriv");
  pfn_glGetSamplerParameterIiv = (PFNGLGETSAMPLERPARAMETERIIVPROC)fnGetProcAddress("glGetSamplerParameterIiv");
  pfn_glGetSamplerParameterfv = (PFNGLGETSAMPLERPARAMETERFVPROC)fnGetProcAddress("glGetSamplerParameterfv");
  pfn_glGetSamplerParameterIuiv = (PFNGLGETSAMPLERPARAMETERIUIVPROC)fnGetProcAddress("glGetSamplerParameterIuiv");
  pfn_glQueryCounter = (PFNGLQUERYCOUNTERPROC)fnGetProcAddress("glQueryCounter");
  pfn_glGetQueryObjecti64v = (PFNGLGETQUERYOBJECTI64VPROC)fnGetProcAddress("glGetQueryObjecti64v");
  pfn_glGetQueryObjectui64v = (PFNGLGETQUERYOBJECTUI64VPROC)fnGetProcAddress("glGetQueryObjectui64v");
  pfn_glVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC)fnGetProcAddress("glVertexAttribDivisor");
  pfn_glVertexAttribP1ui = (PFNGLVERTEXATTRIBP1UIPROC)fnGetProcAddress("glVertexAttribP1ui");
  pfn_glVertexAttribP1uiv = (PFNGLVERTEXATTRIBP1UIVPROC)fnGetProcAddress("glVertexAttribP1uiv");
  pfn_glVertexAttribP2ui = (PFNGLVERTEXATTRIBP2UIPROC)fnGetProcAddress("glVertexAttribP2ui");
  pfn_glVertexAttribP2uiv = (PFNGLVERTEXATTRIBP2UIVPROC)fnGetProcAddress("glVertexAttribP2uiv");
  pfn_glVertexAttribP3ui = (PFNGLVERTEXATTRIBP3UIPROC)fnGetProcAddress("glVertexAttribP3ui");
  pfn_glVertexAttribP3uiv = (PFNGLVERTEXATTRIBP3UIVPROC)fnGetProcAddress("glVertexAttribP3uiv");
  pfn_glVertexAttribP4ui = (PFNGLVERTEXATTRIBP4UIPROC)fnGetProcAddress("glVertexAttribP4ui");
  pfn_glVertexAttribP4uiv = (PFNGLVERTEXATTRIBP4UIVPROC)fnGetProcAddress("glVertexAttribP4uiv");
  int success = has_version(3,3);
  success = success && (pfn_glBindFragDataLocationIndexed != 0);
  success = success && (pfn_glGetFragDataIndex != 0);
  success = success && (pfn_glGenSamplers != 0);
  success = success && (pfn_glDeleteSamplers != 0);
  success = success && (pfn_glIsSampler != 0);
  success = success && (pfn_glBindSampler != 0);
  success = success && (pfn_glSamplerParameteri != 0);
  success = success && (pfn_glSamplerParameteriv != 0);
  success = success && (pfn_glSamplerParameterf != 0);
  success = success && (pfn_glSamplerParameterfv != 0);
  success = success && (pfn_glSamplerParameterIiv != 0);
  success = success && (pfn_glSamplerParameterIuiv != 0);
  success = success && (pfn_glGetSamplerParameteriv != 0);
  success = success && (pfn_glGetSamplerParameterIiv != 0);
  success = success && (pfn_glGetSamplerParameterfv != 0);
  success = success && (pfn_glGetSamplerParameterIuiv != 0);
  success = success && (pfn_glQueryCounter != 0);
  success = success && (pfn_glGetQueryObjecti64v != 0);
  success = success && (pfn_glGetQueryObjectui64v != 0);
  success = success && (pfn_glVertexAttribDivisor != 0);
  success = success && (pfn_glVertexAttribP1ui != 0);
  success = success && (pfn_glVertexAttribP1uiv != 0);
  success = success && (pfn_glVertexAttribP2ui != 0);
  success = success && (pfn_glVertexAttribP2uiv != 0);
  success = success && (pfn_glVertexAttribP3ui != 0);
  success = success && (pfn_glVertexAttribP3uiv != 0);
  success = success && (pfn_glVertexAttribP4ui != 0);
  success = success && (pfn_glVertexAttribP4uiv != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_VERSION_4_0 */

static PFNGLMINSAMPLESHADINGPROC pfn_glMinSampleShading = 0;
static PFNGLBLENDEQUATIONIPROC pfn_glBlendEquationi = 0;
static PFNGLBLENDEQUATIONSEPARATEIPROC pfn_glBlendEquationSeparatei = 0;
static PFNGLBLENDFUNCIPROC pfn_glBlendFunci = 0;
static PFNGLBLENDFUNCSEPARATEIPROC pfn_glBlendFuncSeparatei = 0;
static PFNGLDRAWARRAYSINDIRECTPROC pfn_glDrawArraysIndirect = 0;
static PFNGLDRAWELEMENTSINDIRECTPROC pfn_glDrawElementsIndirect = 0;
static PFNGLUNIFORM1DPROC pfn_glUniform1d = 0;
static PFNGLUNIFORM2DPROC pfn_glUniform2d = 0;
static PFNGLUNIFORM3DPROC pfn_glUniform3d = 0;
static PFNGLUNIFORM4DPROC pfn_glUniform4d = 0;
static PFNGLUNIFORM1DVPROC pfn_glUniform1dv = 0;
static PFNGLUNIFORM2DVPROC pfn_glUniform2dv = 0;
static PFNGLUNIFORM3DVPROC pfn_glUniform3dv = 0;
static PFNGLUNIFORM4DVPROC pfn_glUniform4dv = 0;
static PFNGLUNIFORMMATRIX2DVPROC pfn_glUniformMatrix2dv = 0;
static PFNGLUNIFORMMATRIX3DVPROC pfn_glUniformMatrix3dv = 0;
static PFNGLUNIFORMMATRIX4DVPROC pfn_glUniformMatrix4dv = 0;
static PFNGLUNIFORMMATRIX2X3DVPROC pfn_glUniformMatrix2x3dv = 0;
static PFNGLUNIFORMMATRIX2X4DVPROC pfn_glUniformMatrix2x4dv = 0;
static PFNGLUNIFORMMATRIX3X2DVPROC pfn_glUniformMatrix3x2dv = 0;
static PFNGLUNIFORMMATRIX3X4DVPROC pfn_glUniformMatrix3x4dv = 0;
static PFNGLUNIFORMMATRIX4X2DVPROC pfn_glUniformMatrix4x2dv = 0;
static PFNGLUNIFORMMATRIX4X3DVPROC pfn_glUniformMatrix4x3dv = 0;
static PFNGLGETUNIFORMDVPROC pfn_glGetUniformdv = 0;
static PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC pfn_glGetSubroutineUniformLocation = 0;
static PFNGLGETSUBROUTINEINDEXPROC pfn_glGetSubroutineIndex = 0;
static PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC pfn_glGetActiveSubroutineUniformiv = 0;
static PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC pfn_glGetActiveSubroutineUniformName = 0;
static PFNGLGETACTIVESUBROUTINENAMEPROC pfn_glGetActiveSubroutineName = 0;
static PFNGLUNIFORMSUBROUTINESUIVPROC pfn_glUniformSubroutinesuiv = 0;
static PFNGLGETUNIFORMSUBROUTINEUIVPROC pfn_glGetUniformSubroutineuiv = 0;
static PFNGLGETPROGRAMSTAGEIVPROC pfn_glGetProgramStageiv = 0;
static PFNGLPATCHPARAMETERIPROC pfn_glPatchParameteri = 0;
static PFNGLPATCHPARAMETERFVPROC pfn_glPatchParameterfv = 0;
static PFNGLBINDTRANSFORMFEEDBACKPROC pfn_glBindTransformFeedback = 0;
static PFNGLDELETETRANSFORMFEEDBACKSPROC pfn_glDeleteTransformFeedbacks = 0;
static PFNGLGENTRANSFORMFEEDBACKSPROC pfn_glGenTransformFeedbacks = 0;
static PFNGLISTRANSFORMFEEDBACKPROC pfn_glIsTransformFeedback = 0;
static PFNGLPAUSETRANSFORMFEEDBACKPROC pfn_glPauseTransformFeedback = 0;
static PFNGLRESUMETRANSFORMFEEDBACKPROC pfn_glResumeTransformFeedback = 0;
static PFNGLDRAWTRANSFORMFEEDBACKPROC pfn_glDrawTransformFeedback = 0;
static PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC pfn_glDrawTransformFeedbackStream = 0;
static PFNGLBEGINQUERYINDEXEDPROC pfn_glBeginQueryIndexed = 0;
static PFNGLENDQUERYINDEXEDPROC pfn_glEndQueryIndexed = 0;
static PFNGLGETQUERYINDEXEDIVPROC pfn_glGetQueryIndexediv = 0;

GLAPI void APIENTRY glMinSampleShading(GLfloat value)
{
  assert(pfn_glMinSampleShading);
  pfn_glMinSampleShading(value);
}
GLAPI void APIENTRY glBlendEquationi(GLuint buf, GLenum mode)
{
  assert(pfn_glBlendEquationi);
  pfn_glBlendEquationi(buf,mode);
}
GLAPI void APIENTRY glBlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha)
{
  assert(pfn_glBlendEquationSeparatei);
  pfn_glBlendEquationSeparatei(buf,modeRGB,modeAlpha);
}
GLAPI void APIENTRY glBlendFunci(GLuint buf, GLenum src, GLenum dst)
{
  assert(pfn_glBlendFunci);
  pfn_glBlendFunci(buf,src,dst);
}
GLAPI void APIENTRY glBlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
  assert(pfn_glBlendFuncSeparatei);
  pfn_glBlendFuncSeparatei(buf,srcRGB,dstRGB,srcAlpha,dstAlpha);
}
GLAPI void APIENTRY glDrawArraysIndirect(GLenum mode, const void* indirect)
{
  assert(pfn_glDrawArraysIndirect);
  pfn_glDrawArraysIndirect(mode,indirect);
}
GLAPI void APIENTRY glDrawElementsIndirect(GLenum mode, GLenum type, const void* indirect)
{
  assert(pfn_glDrawElementsIndirect);
  pfn_glDrawElementsIndirect(mode,type,indirect);
}
GLAPI void APIENTRY glUniform1d(GLint location, GLdouble x)
{
  assert(pfn_glUniform1d);
  pfn_glUniform1d(location,x);
}
GLAPI void APIENTRY glUniform2d(GLint location, GLdouble x, GLdouble y)
{
  assert(pfn_glUniform2d);
  pfn_glUniform2d(location,x,y);
}
GLAPI void APIENTRY glUniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z)
{
  assert(pfn_glUniform3d);
  pfn_glUniform3d(location,x,y,z);
}
GLAPI void APIENTRY glUniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
  assert(pfn_glUniform4d);
  pfn_glUniform4d(location,x,y,z,w);
}
GLAPI void APIENTRY glUniform1dv(GLint location, GLsizei count, const GLdouble* value)
{
  assert(pfn_glUniform1dv);
  pfn_glUniform1dv(location,count,value);
}
GLAPI void APIENTRY glUniform2dv(GLint location, GLsizei count, const GLdouble* value)
{
  assert(pfn_glUniform2dv);
  pfn_glUniform2dv(location,count,value);
}
GLAPI void APIENTRY glUniform3dv(GLint location, GLsizei count, const GLdouble* value)
{
  assert(pfn_glUniform3dv);
  pfn_glUniform3dv(location,count,value);
}
GLAPI void APIENTRY glUniform4dv(GLint location, GLsizei count, const GLdouble* value)
{
  assert(pfn_glUniform4dv);
  pfn_glUniform4dv(location,count,value);
}
GLAPI void APIENTRY glUniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  assert(pfn_glUniformMatrix2dv);
  pfn_glUniformMatrix2dv(location,count,transpose,value);
}
GLAPI void APIENTRY glUniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  assert(pfn_glUniformMatrix3dv);
  pfn_glUniformMatrix3dv(location,count,transpose,value);
}
GLAPI void APIENTRY glUniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  assert(pfn_glUniformMatrix4dv);
  pfn_glUniformMatrix4dv(location,count,transpose,value);
}
GLAPI void APIENTRY glUniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  assert(pfn_glUniformMatrix2x3dv);
  pfn_glUniformMatrix2x3dv(location,count,transpose,value);
}
GLAPI void APIENTRY glUniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  assert(pfn_glUniformMatrix2x4dv);
  pfn_glUniformMatrix2x4dv(location,count,transpose,value);
}
GLAPI void APIENTRY glUniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  assert(pfn_glUniformMatrix3x2dv);
  pfn_glUniformMatrix3x2dv(location,count,transpose,value);
}
GLAPI void APIENTRY glUniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  assert(pfn_glUniformMatrix3x4dv);
  pfn_glUniformMatrix3x4dv(location,count,transpose,value);
}
GLAPI void APIENTRY glUniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  assert(pfn_glUniformMatrix4x2dv);
  pfn_glUniformMatrix4x2dv(location,count,transpose,value);
}
GLAPI void APIENTRY glUniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  assert(pfn_glUniformMatrix4x3dv);
  pfn_glUniformMatrix4x3dv(location,count,transpose,value);
}
GLAPI void APIENTRY glGetUniformdv(GLuint program, GLint location, GLdouble* params)
{
  assert(pfn_glGetUniformdv);
  pfn_glGetUniformdv(program,location,params);
}
GLAPI GLint APIENTRY glGetSubroutineUniformLocation(GLuint program, GLenum shadertype, const GLchar* name)
{
  assert(pfn_glGetSubroutineUniformLocation);
  return pfn_glGetSubroutineUniformLocation(program,shadertype,name);
}
GLAPI GLuint APIENTRY glGetSubroutineIndex(GLuint program, GLenum shadertype, const GLchar* name)
{
  assert(pfn_glGetSubroutineIndex);
  return pfn_glGetSubroutineIndex(program,shadertype,name);
}
GLAPI void APIENTRY glGetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint* values)
{
  assert(pfn_glGetActiveSubroutineUniformiv);
  pfn_glGetActiveSubroutineUniformiv(program,shadertype,index,pname,values);
}
GLAPI void APIENTRY glGetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei* length, GLchar* name)
{
  assert(pfn_glGetActiveSubroutineUniformName);
  pfn_glGetActiveSubroutineUniformName(program,shadertype,index,bufsize,length,name);
}
GLAPI void APIENTRY glGetActiveSubroutineName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei* length, GLchar* name)
{
  assert(pfn_glGetActiveSubroutineName);
  pfn_glGetActiveSubroutineName(program,shadertype,index,bufsize,length,name);
}
GLAPI void APIENTRY glUniformSubroutinesuiv(GLenum shadertype, GLsizei count, const GLuint* indices)
{
  assert(pfn_glUniformSubroutinesuiv);
  pfn_glUniformSubroutinesuiv(shadertype,count,indices);
}
GLAPI void APIENTRY glGetUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint* params)
{
  assert(pfn_glGetUniformSubroutineuiv);
  pfn_glGetUniformSubroutineuiv(shadertype,location,params);
}
GLAPI void APIENTRY glGetProgramStageiv(GLuint program, GLenum shadertype, GLenum pname, GLint* values)
{
  assert(pfn_glGetProgramStageiv);
  pfn_glGetProgramStageiv(program,shadertype,pname,values);
}
GLAPI void APIENTRY glPatchParameteri(GLenum pname, GLint value)
{
  assert(pfn_glPatchParameteri);
  pfn_glPatchParameteri(pname,value);
}
GLAPI void APIENTRY glPatchParameterfv(GLenum pname, const GLfloat* values)
{
  assert(pfn_glPatchParameterfv);
  pfn_glPatchParameterfv(pname,values);
}
GLAPI void APIENTRY glBindTransformFeedback(GLenum target, GLuint id)
{
  assert(pfn_glBindTransformFeedback);
  pfn_glBindTransformFeedback(target,id);
}
GLAPI void APIENTRY glDeleteTransformFeedbacks(GLsizei n, const GLuint* ids)
{
  assert(pfn_glDeleteTransformFeedbacks);
  pfn_glDeleteTransformFeedbacks(n,ids);
}
GLAPI void APIENTRY glGenTransformFeedbacks(GLsizei n, GLuint* ids)
{
  assert(pfn_glGenTransformFeedbacks);
  pfn_glGenTransformFeedbacks(n,ids);
}
GLAPI GLboolean APIENTRY glIsTransformFeedback(GLuint id)
{
  assert(pfn_glIsTransformFeedback);
  return pfn_glIsTransformFeedback(id);
}
GLAPI void APIENTRY glPauseTransformFeedback(void)
{
  assert(pfn_glPauseTransformFeedback);
  pfn_glPauseTransformFeedback();
}
GLAPI void APIENTRY glResumeTransformFeedback(void)
{
  assert(pfn_glResumeTransformFeedback);
  pfn_glResumeTransformFeedback();
}
GLAPI void APIENTRY glDrawTransformFeedback(GLenum mode, GLuint id)
{
  assert(pfn_glDrawTransformFeedback);
  pfn_glDrawTransformFeedback(mode,id);
}
GLAPI void APIENTRY glDrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream)
{
  assert(pfn_glDrawTransformFeedbackStream);
  pfn_glDrawTransformFeedbackStream(mode,id,stream);
}
GLAPI void APIENTRY glBeginQueryIndexed(GLenum target, GLuint index, GLuint id)
{
  assert(pfn_glBeginQueryIndexed);
  pfn_glBeginQueryIndexed(target,index,id);
}
GLAPI void APIENTRY glEndQueryIndexed(GLenum target, GLuint index)
{
  assert(pfn_glEndQueryIndexed);
  pfn_glEndQueryIndexed(target,index);
}
GLAPI void APIENTRY glGetQueryIndexediv(GLenum target, GLuint index, GLenum pname, GLint* params)
{
  assert(pfn_glGetQueryIndexediv);
  pfn_glGetQueryIndexediv(target,index,pname,params);
}

int load_GL_VERSION_4_0(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glMinSampleShading = (PFNGLMINSAMPLESHADINGPROC)fnGetProcAddress("glMinSampleShading");
  pfn_glBlendEquationi = (PFNGLBLENDEQUATIONIPROC)fnGetProcAddress("glBlendEquationi");
  pfn_glBlendEquationSeparatei = (PFNGLBLENDEQUATIONSEPARATEIPROC)fnGetProcAddress("glBlendEquationSeparatei");
  pfn_glBlendFunci = (PFNGLBLENDFUNCIPROC)fnGetProcAddress("glBlendFunci");
  pfn_glBlendFuncSeparatei = (PFNGLBLENDFUNCSEPARATEIPROC)fnGetProcAddress("glBlendFuncSeparatei");
  pfn_glDrawArraysIndirect = (PFNGLDRAWARRAYSINDIRECTPROC)fnGetProcAddress("glDrawArraysIndirect");
  pfn_glDrawElementsIndirect = (PFNGLDRAWELEMENTSINDIRECTPROC)fnGetProcAddress("glDrawElementsIndirect");
  pfn_glUniform1d = (PFNGLUNIFORM1DPROC)fnGetProcAddress("glUniform1d");
  pfn_glUniform2d = (PFNGLUNIFORM2DPROC)fnGetProcAddress("glUniform2d");
  pfn_glUniform3d = (PFNGLUNIFORM3DPROC)fnGetProcAddress("glUniform3d");
  pfn_glUniform4d = (PFNGLUNIFORM4DPROC)fnGetProcAddress("glUniform4d");
  pfn_glUniform1dv = (PFNGLUNIFORM1DVPROC)fnGetProcAddress("glUniform1dv");
  pfn_glUniform2dv = (PFNGLUNIFORM2DVPROC)fnGetProcAddress("glUniform2dv");
  pfn_glUniform3dv = (PFNGLUNIFORM3DVPROC)fnGetProcAddress("glUniform3dv");
  pfn_glUniform4dv = (PFNGLUNIFORM4DVPROC)fnGetProcAddress("glUniform4dv");
  pfn_glUniformMatrix2dv = (PFNGLUNIFORMMATRIX2DVPROC)fnGetProcAddress("glUniformMatrix2dv");
  pfn_glUniformMatrix3dv = (PFNGLUNIFORMMATRIX3DVPROC)fnGetProcAddress("glUniformMatrix3dv");
  pfn_glUniformMatrix4dv = (PFNGLUNIFORMMATRIX4DVPROC)fnGetProcAddress("glUniformMatrix4dv");
  pfn_glUniformMatrix2x3dv = (PFNGLUNIFORMMATRIX2X3DVPROC)fnGetProcAddress("glUniformMatrix2x3dv");
  pfn_glUniformMatrix2x4dv = (PFNGLUNIFORMMATRIX2X4DVPROC)fnGetProcAddress("glUniformMatrix2x4dv");
  pfn_glUniformMatrix3x2dv = (PFNGLUNIFORMMATRIX3X2DVPROC)fnGetProcAddress("glUniformMatrix3x2dv");
  pfn_glUniformMatrix3x4dv = (PFNGLUNIFORMMATRIX3X4DVPROC)fnGetProcAddress("glUniformMatrix3x4dv");
  pfn_glUniformMatrix4x2dv = (PFNGLUNIFORMMATRIX4X2DVPROC)fnGetProcAddress("glUniformMatrix4x2dv");
  pfn_glUniformMatrix4x3dv = (PFNGLUNIFORMMATRIX4X3DVPROC)fnGetProcAddress("glUniformMatrix4x3dv");
  pfn_glGetUniformdv = (PFNGLGETUNIFORMDVPROC)fnGetProcAddress("glGetUniformdv");
  pfn_glGetSubroutineUniformLocation = (PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC)fnGetProcAddress("glGetSubroutineUniformLocation");
  pfn_glGetSubroutineIndex = (PFNGLGETSUBROUTINEINDEXPROC)fnGetProcAddress("glGetSubroutineIndex");
  pfn_glGetActiveSubroutineUniformiv = (PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC)fnGetProcAddress("glGetActiveSubroutineUniformiv");
  pfn_glGetActiveSubroutineUniformName = (PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC)fnGetProcAddress("glGetActiveSubroutineUniformName");
  pfn_glGetActiveSubroutineName = (PFNGLGETACTIVESUBROUTINENAMEPROC)fnGetProcAddress("glGetActiveSubroutineName");
  pfn_glUniformSubroutinesuiv = (PFNGLUNIFORMSUBROUTINESUIVPROC)fnGetProcAddress("glUniformSubroutinesuiv");
  pfn_glGetUniformSubroutineuiv = (PFNGLGETUNIFORMSUBROUTINEUIVPROC)fnGetProcAddress("glGetUniformSubroutineuiv");
  pfn_glGetProgramStageiv = (PFNGLGETPROGRAMSTAGEIVPROC)fnGetProcAddress("glGetProgramStageiv");
  pfn_glPatchParameteri = (PFNGLPATCHPARAMETERIPROC)fnGetProcAddress("glPatchParameteri");
  pfn_glPatchParameterfv = (PFNGLPATCHPARAMETERFVPROC)fnGetProcAddress("glPatchParameterfv");
  pfn_glBindTransformFeedback = (PFNGLBINDTRANSFORMFEEDBACKPROC)fnGetProcAddress("glBindTransformFeedback");
  pfn_glDeleteTransformFeedbacks = (PFNGLDELETETRANSFORMFEEDBACKSPROC)fnGetProcAddress("glDeleteTransformFeedbacks");
  pfn_glGenTransformFeedbacks = (PFNGLGENTRANSFORMFEEDBACKSPROC)fnGetProcAddress("glGenTransformFeedbacks");
  pfn_glIsTransformFeedback = (PFNGLISTRANSFORMFEEDBACKPROC)fnGetProcAddress("glIsTransformFeedback");
  pfn_glPauseTransformFeedback = (PFNGLPAUSETRANSFORMFEEDBACKPROC)fnGetProcAddress("glPauseTransformFeedback");
  pfn_glResumeTransformFeedback = (PFNGLRESUMETRANSFORMFEEDBACKPROC)fnGetProcAddress("glResumeTransformFeedback");
  pfn_glDrawTransformFeedback = (PFNGLDRAWTRANSFORMFEEDBACKPROC)fnGetProcAddress("glDrawTransformFeedback");
  pfn_glDrawTransformFeedbackStream = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC)fnGetProcAddress("glDrawTransformFeedbackStream");
  pfn_glBeginQueryIndexed = (PFNGLBEGINQUERYINDEXEDPROC)fnGetProcAddress("glBeginQueryIndexed");
  pfn_glEndQueryIndexed = (PFNGLENDQUERYINDEXEDPROC)fnGetProcAddress("glEndQueryIndexed");
  pfn_glGetQueryIndexediv = (PFNGLGETQUERYINDEXEDIVPROC)fnGetProcAddress("glGetQueryIndexediv");
  int success = has_version(4,0);
  success = success && (pfn_glMinSampleShading != 0);
  success = success && (pfn_glBlendEquationi != 0);
  success = success && (pfn_glBlendEquationSeparatei != 0);
  success = success && (pfn_glBlendFunci != 0);
  success = success && (pfn_glBlendFuncSeparatei != 0);
  success = success && (pfn_glDrawArraysIndirect != 0);
  success = success && (pfn_glDrawElementsIndirect != 0);
  success = success && (pfn_glUniform1d != 0);
  success = success && (pfn_glUniform2d != 0);
  success = success && (pfn_glUniform3d != 0);
  success = success && (pfn_glUniform4d != 0);
  success = success && (pfn_glUniform1dv != 0);
  success = success && (pfn_glUniform2dv != 0);
  success = success && (pfn_glUniform3dv != 0);
  success = success && (pfn_glUniform4dv != 0);
  success = success && (pfn_glUniformMatrix2dv != 0);
  success = success && (pfn_glUniformMatrix3dv != 0);
  success = success && (pfn_glUniformMatrix4dv != 0);
  success = success && (pfn_glUniformMatrix2x3dv != 0);
  success = success && (pfn_glUniformMatrix2x4dv != 0);
  success = success && (pfn_glUniformMatrix3x2dv != 0);
  success = success && (pfn_glUniformMatrix3x4dv != 0);
  success = success && (pfn_glUniformMatrix4x2dv != 0);
  success = success && (pfn_glUniformMatrix4x3dv != 0);
  success = success && (pfn_glGetUniformdv != 0);
  success = success && (pfn_glGetSubroutineUniformLocation != 0);
  success = success && (pfn_glGetSubroutineIndex != 0);
  success = success && (pfn_glGetActiveSubroutineUniformiv != 0);
  success = success && (pfn_glGetActiveSubroutineUniformName != 0);
  success = success && (pfn_glGetActiveSubroutineName != 0);
  success = success && (pfn_glUniformSubroutinesuiv != 0);
  success = success && (pfn_glGetUniformSubroutineuiv != 0);
  success = success && (pfn_glGetProgramStageiv != 0);
  success = success && (pfn_glPatchParameteri != 0);
  success = success && (pfn_glPatchParameterfv != 0);
  success = success && (pfn_glBindTransformFeedback != 0);
  success = success && (pfn_glDeleteTransformFeedbacks != 0);
  success = success && (pfn_glGenTransformFeedbacks != 0);
  success = success && (pfn_glIsTransformFeedback != 0);
  success = success && (pfn_glPauseTransformFeedback != 0);
  success = success && (pfn_glResumeTransformFeedback != 0);
  success = success && (pfn_glDrawTransformFeedback != 0);
  success = success && (pfn_glDrawTransformFeedbackStream != 0);
  success = success && (pfn_glBeginQueryIndexed != 0);
  success = success && (pfn_glEndQueryIndexed != 0);
  success = success && (pfn_glGetQueryIndexediv != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_VERSION_4_1 */

static PFNGLRELEASESHADERCOMPILERPROC pfn_glReleaseShaderCompiler = 0;
static PFNGLSHADERBINARYPROC pfn_glShaderBinary = 0;
static PFNGLGETSHADERPRECISIONFORMATPROC pfn_glGetShaderPrecisionFormat = 0;
static PFNGLDEPTHRANGEFPROC pfn_glDepthRangef = 0;
static PFNGLCLEARDEPTHFPROC pfn_glClearDepthf = 0;
static PFNGLGETPROGRAMBINARYPROC pfn_glGetProgramBinary = 0;
static PFNGLPROGRAMBINARYPROC pfn_glProgramBinary = 0;
static PFNGLPROGRAMPARAMETERIPROC pfn_glProgramParameteri = 0;
static PFNGLUSEPROGRAMSTAGESPROC pfn_glUseProgramStages = 0;
static PFNGLACTIVESHADERPROGRAMPROC pfn_glActiveShaderProgram = 0;
static PFNGLCREATESHADERPROGRAMVPROC pfn_glCreateShaderProgramv = 0;
static PFNGLBINDPROGRAMPIPELINEPROC pfn_glBindProgramPipeline = 0;
static PFNGLDELETEPROGRAMPIPELINESPROC pfn_glDeleteProgramPipelines = 0;
static PFNGLGENPROGRAMPIPELINESPROC pfn_glGenProgramPipelines = 0;
static PFNGLISPROGRAMPIPELINEPROC pfn_glIsProgramPipeline = 0;
static PFNGLGETPROGRAMPIPELINEIVPROC pfn_glGetProgramPipelineiv = 0;
static PFNGLPROGRAMUNIFORM1IPROC pfn_glProgramUniform1i = 0;
static PFNGLPROGRAMUNIFORM1IVPROC pfn_glProgramUniform1iv = 0;
static PFNGLPROGRAMUNIFORM1FPROC pfn_glProgramUniform1f = 0;
static PFNGLPROGRAMUNIFORM1FVPROC pfn_glProgramUniform1fv = 0;
static PFNGLPROGRAMUNIFORM1DPROC pfn_glProgramUniform1d = 0;
static PFNGLPROGRAMUNIFORM1DVPROC pfn_glProgramUniform1dv = 0;
static PFNGLPROGRAMUNIFORM1UIPROC pfn_glProgramUniform1ui = 0;
static PFNGLPROGRAMUNIFORM1UIVPROC pfn_glProgramUniform1uiv = 0;
static PFNGLPROGRAMUNIFORM2IPROC pfn_glProgramUniform2i = 0;
static PFNGLPROGRAMUNIFORM2IVPROC pfn_glProgramUniform2iv = 0;
static PFNGLPROGRAMUNIFORM2FPROC pfn_glProgramUniform2f = 0;
static PFNGLPROGRAMUNIFORM2FVPROC pfn_glProgramUniform2fv = 0;
static PFNGLPROGRAMUNIFORM2DPROC pfn_glProgramUniform2d = 0;
static PFNGLPROGRAMUNIFORM2DVPROC pfn_glProgramUniform2dv = 0;
static PFNGLPROGRAMUNIFORM2UIPROC pfn_glProgramUniform2ui = 0;
static PFNGLPROGRAMUNIFORM2UIVPROC pfn_glProgramUniform2uiv = 0;
static PFNGLPROGRAMUNIFORM3IPROC pfn_glProgramUniform3i = 0;
static PFNGLPROGRAMUNIFORM3IVPROC pfn_glProgramUniform3iv = 0;
static PFNGLPROGRAMUNIFORM3FPROC pfn_glProgramUniform3f = 0;
static PFNGLPROGRAMUNIFORM3FVPROC pfn_glProgramUniform3fv = 0;
static PFNGLPROGRAMUNIFORM3DPROC pfn_glProgramUniform3d = 0;
static PFNGLPROGRAMUNIFORM3DVPROC pfn_glProgramUniform3dv = 0;
static PFNGLPROGRAMUNIFORM3UIPROC pfn_glProgramUniform3ui = 0;
static PFNGLPROGRAMUNIFORM3UIVPROC pfn_glProgramUniform3uiv = 0;
static PFNGLPROGRAMUNIFORM4IPROC pfn_glProgramUniform4i = 0;
static PFNGLPROGRAMUNIFORM4IVPROC pfn_glProgramUniform4iv = 0;
static PFNGLPROGRAMUNIFORM4FPROC pfn_glProgramUniform4f = 0;
static PFNGLPROGRAMUNIFORM4FVPROC pfn_glProgramUniform4fv = 0;
static PFNGLPROGRAMUNIFORM4DPROC pfn_glProgramUniform4d = 0;
static PFNGLPROGRAMUNIFORM4DVPROC pfn_glProgramUniform4dv = 0;
static PFNGLPROGRAMUNIFORM4UIPROC pfn_glProgramUniform4ui = 0;
static PFNGLPROGRAMUNIFORM4UIVPROC pfn_glProgramUniform4uiv = 0;
static PFNGLPROGRAMUNIFORMMATRIX2FVPROC pfn_glProgramUniformMatrix2fv = 0;
static PFNGLPROGRAMUNIFORMMATRIX3FVPROC pfn_glProgramUniformMatrix3fv = 0;
static PFNGLPROGRAMUNIFORMMATRIX4FVPROC pfn_glProgramUniformMatrix4fv = 0;
static PFNGLPROGRAMUNIFORMMATRIX2DVPROC pfn_glProgramUniformMatrix2dv = 0;
static PFNGLPROGRAMUNIFORMMATRIX3DVPROC pfn_glProgramUniformMatrix3dv = 0;
static PFNGLPROGRAMUNIFORMMATRIX4DVPROC pfn_glProgramUniformMatrix4dv = 0;
static PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC pfn_glProgramUniformMatrix2x3fv = 0;
static PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC pfn_glProgramUniformMatrix3x2fv = 0;
static PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC pfn_glProgramUniformMatrix2x4fv = 0;
static PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC pfn_glProgramUniformMatrix4x2fv = 0;
static PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC pfn_glProgramUniformMatrix3x4fv = 0;
static PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC pfn_glProgramUniformMatrix4x3fv = 0;
static PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC pfn_glProgramUniformMatrix2x3dv = 0;
static PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC pfn_glProgramUniformMatrix3x2dv = 0;
static PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC pfn_glProgramUniformMatrix2x4dv = 0;
static PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC pfn_glProgramUniformMatrix4x2dv = 0;
static PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC pfn_glProgramUniformMatrix3x4dv = 0;
static PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC pfn_glProgramUniformMatrix4x3dv = 0;
static PFNGLVALIDATEPROGRAMPIPELINEPROC pfn_glValidateProgramPipeline = 0;
static PFNGLGETPROGRAMPIPELINEINFOLOGPROC pfn_glGetProgramPipelineInfoLog = 0;
static PFNGLVERTEXATTRIBL1DPROC pfn_glVertexAttribL1d = 0;
static PFNGLVERTEXATTRIBL2DPROC pfn_glVertexAttribL2d = 0;
static PFNGLVERTEXATTRIBL3DPROC pfn_glVertexAttribL3d = 0;
static PFNGLVERTEXATTRIBL4DPROC pfn_glVertexAttribL4d = 0;
static PFNGLVERTEXATTRIBL1DVPROC pfn_glVertexAttribL1dv = 0;
static PFNGLVERTEXATTRIBL2DVPROC pfn_glVertexAttribL2dv = 0;
static PFNGLVERTEXATTRIBL3DVPROC pfn_glVertexAttribL3dv = 0;
static PFNGLVERTEXATTRIBL4DVPROC pfn_glVertexAttribL4dv = 0;
static PFNGLVERTEXATTRIBLPOINTERPROC pfn_glVertexAttribLPointer = 0;
static PFNGLGETVERTEXATTRIBLDVPROC pfn_glGetVertexAttribLdv = 0;
static PFNGLVIEWPORTARRAYVPROC pfn_glViewportArrayv = 0;
static PFNGLVIEWPORTINDEXEDFPROC pfn_glViewportIndexedf = 0;
static PFNGLVIEWPORTINDEXEDFVPROC pfn_glViewportIndexedfv = 0;
static PFNGLSCISSORARRAYVPROC pfn_glScissorArrayv = 0;
static PFNGLSCISSORINDEXEDPROC pfn_glScissorIndexed = 0;
static PFNGLSCISSORINDEXEDVPROC pfn_glScissorIndexedv = 0;
static PFNGLDEPTHRANGEARRAYVPROC pfn_glDepthRangeArrayv = 0;
static PFNGLDEPTHRANGEINDEXEDPROC pfn_glDepthRangeIndexed = 0;
static PFNGLGETFLOATI_VPROC pfn_glGetFloati_v = 0;
static PFNGLGETDOUBLEI_VPROC pfn_glGetDoublei_v = 0;

GLAPI void APIENTRY glReleaseShaderCompiler(void)
{
  assert(pfn_glReleaseShaderCompiler);
  pfn_glReleaseShaderCompiler();
}
GLAPI void APIENTRY glShaderBinary(GLsizei count, const GLuint* shaders, GLenum binaryformat, const void* binary, GLsizei length)
{
  assert(pfn_glShaderBinary);
  pfn_glShaderBinary(count,shaders,binaryformat,binary,length);
}
GLAPI void APIENTRY glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision)
{
  assert(pfn_glGetShaderPrecisionFormat);
  pfn_glGetShaderPrecisionFormat(shadertype,precisiontype,range,precision);
}
GLAPI void APIENTRY glDepthRangef(GLfloat n, GLfloat f)
{
  assert(pfn_glDepthRangef);
  pfn_glDepthRangef(n,f);
}
GLAPI void APIENTRY glClearDepthf(GLfloat d)
{
  assert(pfn_glClearDepthf);
  pfn_glClearDepthf(d);
}
GLAPI void APIENTRY glGetProgramBinary(GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, void* binary)
{
  assert(pfn_glGetProgramBinary);
  pfn_glGetProgramBinary(program,bufSize,length,binaryFormat,binary);
}
GLAPI void APIENTRY glProgramBinary(GLuint program, GLenum binaryFormat, const void* binary, GLsizei length)
{
  assert(pfn_glProgramBinary);
  pfn_glProgramBinary(program,binaryFormat,binary,length);
}
GLAPI void APIENTRY glProgramParameteri(GLuint program, GLenum pname, GLint value)
{
  assert(pfn_glProgramParameteri);
  pfn_glProgramParameteri(program,pname,value);
}
GLAPI void APIENTRY glUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program)
{
  assert(pfn_glUseProgramStages);
  pfn_glUseProgramStages(pipeline,stages,program);
}
GLAPI void APIENTRY glActiveShaderProgram(GLuint pipeline, GLuint program)
{
  assert(pfn_glActiveShaderProgram);
  pfn_glActiveShaderProgram(pipeline,program);
}
GLAPI GLuint APIENTRY glCreateShaderProgramv(GLenum type, GLsizei count, const GLchar* const* strings)
{
  assert(pfn_glCreateShaderProgramv);
  return pfn_glCreateShaderProgramv(type,count,strings);
}
GLAPI void APIENTRY glBindProgramPipeline(GLuint pipeline)
{
  assert(pfn_glBindProgramPipeline);
  pfn_glBindProgramPipeline(pipeline);
}
GLAPI void APIENTRY glDeleteProgramPipelines(GLsizei n, const GLuint* pipelines)
{
  assert(pfn_glDeleteProgramPipelines);
  pfn_glDeleteProgramPipelines(n,pipelines);
}
GLAPI void APIENTRY glGenProgramPipelines(GLsizei n, GLuint* pipelines)
{
  assert(pfn_glGenProgramPipelines);
  pfn_glGenProgramPipelines(n,pipelines);
}
GLAPI GLboolean APIENTRY glIsProgramPipeline(GLuint pipeline)
{
  assert(pfn_glIsProgramPipeline);
  return pfn_glIsProgramPipeline(pipeline);
}
GLAPI void APIENTRY glGetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint* params)
{
  assert(pfn_glGetProgramPipelineiv);
  pfn_glGetProgramPipelineiv(pipeline,pname,params);
}
GLAPI void APIENTRY glProgramUniform1i(GLuint program, GLint location, GLint v0)
{
  assert(pfn_glProgramUniform1i);
  pfn_glProgramUniform1i(program,location,v0);
}
GLAPI void APIENTRY glProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint* value)
{
  assert(pfn_glProgramUniform1iv);
  pfn_glProgramUniform1iv(program,location,count,value);
}
GLAPI void APIENTRY glProgramUniform1f(GLuint program, GLint location, GLfloat v0)
{
  assert(pfn_glProgramUniform1f);
  pfn_glProgramUniform1f(program,location,v0);
}
GLAPI void APIENTRY glProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat* value)
{
  assert(pfn_glProgramUniform1fv);
  pfn_glProgramUniform1fv(program,location,count,value);
}
GLAPI void APIENTRY glProgramUniform1d(GLuint program, GLint location, GLdouble v0)
{
  assert(pfn_glProgramUniform1d);
  pfn_glProgramUniform1d(program,location,v0);
}
GLAPI void APIENTRY glProgramUniform1dv(GLuint program, GLint location, GLsizei count, const GLdouble* value)
{
  assert(pfn_glProgramUniform1dv);
  pfn_glProgramUniform1dv(program,location,count,value);
}
GLAPI void APIENTRY glProgramUniform1ui(GLuint program, GLint location, GLuint v0)
{
  assert(pfn_glProgramUniform1ui);
  pfn_glProgramUniform1ui(program,location,v0);
}
GLAPI void APIENTRY glProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint* value)
{
  assert(pfn_glProgramUniform1uiv);
  pfn_glProgramUniform1uiv(program,location,count,value);
}
GLAPI void APIENTRY glProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1)
{
  assert(pfn_glProgramUniform2i);
  pfn_glProgramUniform2i(program,location,v0,v1);
}
GLAPI void APIENTRY glProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint* value)
{
  assert(pfn_glProgramUniform2iv);
  pfn_glProgramUniform2iv(program,location,count,value);
}
GLAPI void APIENTRY glProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1)
{
  assert(pfn_glProgramUniform2f);
  pfn_glProgramUniform2f(program,location,v0,v1);
}
GLAPI void APIENTRY glProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat* value)
{
  assert(pfn_glProgramUniform2fv);
  pfn_glProgramUniform2fv(program,location,count,value);
}
GLAPI void APIENTRY glProgramUniform2d(GLuint program, GLint location, GLdouble v0, GLdouble v1)
{
  assert(pfn_glProgramUniform2d);
  pfn_glProgramUniform2d(program,location,v0,v1);
}
GLAPI void APIENTRY glProgramUniform2dv(GLuint program, GLint location, GLsizei count, const GLdouble* value)
{
  assert(pfn_glProgramUniform2dv);
  pfn_glProgramUniform2dv(program,location,count,value);
}
GLAPI void APIENTRY glProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1)
{
  assert(pfn_glProgramUniform2ui);
  pfn_glProgramUniform2ui(program,location,v0,v1);
}
GLAPI void APIENTRY glProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint* value)
{
  assert(pfn_glProgramUniform2uiv);
  pfn_glProgramUniform2uiv(program,location,count,value);
}
GLAPI void APIENTRY glProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2)
{
  assert(pfn_glProgramUniform3i);
  pfn_glProgramUniform3i(program,location,v0,v1,v2);
}
GLAPI void APIENTRY glProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint* value)
{
  assert(pfn_glProgramUniform3iv);
  pfn_glProgramUniform3iv(program,location,count,value);
}
GLAPI void APIENTRY glProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
  assert(pfn_glProgramUniform3f);
  pfn_glProgramUniform3f(program,location,v0,v1,v2);
}
GLAPI void APIENTRY glProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat* value)
{
  assert(pfn_glProgramUniform3fv);
  pfn_glProgramUniform3fv(program,location,count,value);
}
GLAPI void APIENTRY glProgramUniform3d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2)
{
  assert(pfn_glProgramUniform3d);
  pfn_glProgramUniform3d(program,location,v0,v1,v2);
}
GLAPI void APIENTRY glProgramUniform3dv(GLuint program, GLint location, GLsizei count, const GLdouble* value)
{
  assert(pfn_glProgramUniform3dv);
  pfn_glProgramUniform3dv(program,location,count,value);
}
GLAPI void APIENTRY glProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2)
{
  assert(pfn_glProgramUniform3ui);
  pfn_glProgramUniform3ui(program,location,v0,v1,v2);
}
GLAPI void APIENTRY glProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint* value)
{
  assert(pfn_glProgramUniform3uiv);
  pfn_glProgramUniform3uiv(program,location,count,value);
}
GLAPI void APIENTRY glProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
  assert(pfn_glProgramUniform4i);
  pfn_glProgramUniform4i(program,location,v0,v1,v2,v3);
}
GLAPI void APIENTRY glProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint* value)
{
  assert(pfn_glProgramUniform4iv);
  pfn_glProgramUniform4iv(program,location,count,value);
}
GLAPI void APIENTRY glProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
  assert(pfn_glProgramUniform4f);
  pfn_glProgramUniform4f(program,location,v0,v1,v2,v3);
}
GLAPI void APIENTRY glProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat* value)
{
  assert(pfn_glProgramUniform4fv);
  pfn_glProgramUniform4fv(program,location,count,value);
}
GLAPI void APIENTRY glProgramUniform4d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3)
{
  assert(pfn_glProgramUniform4d);
  pfn_glProgramUniform4d(program,location,v0,v1,v2,v3);
}
GLAPI void APIENTRY glProgramUniform4dv(GLuint program, GLint location, GLsizei count, const GLdouble* value)
{
  assert(pfn_glProgramUniform4dv);
  pfn_glProgramUniform4dv(program,location,count,value);
}
GLAPI void APIENTRY glProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
  assert(pfn_glProgramUniform4ui);
  pfn_glProgramUniform4ui(program,location,v0,v1,v2,v3);
}
GLAPI void APIENTRY glProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint* value)
{
  assert(pfn_glProgramUniform4uiv);
  pfn_glProgramUniform4uiv(program,location,count,value);
}
GLAPI void APIENTRY glProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  assert(pfn_glProgramUniformMatrix2fv);
  pfn_glProgramUniformMatrix2fv(program,location,count,transpose,value);
}
GLAPI void APIENTRY glProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  assert(pfn_glProgramUniformMatrix3fv);
  pfn_glProgramUniformMatrix3fv(program,location,count,transpose,value);
}
GLAPI void APIENTRY glProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  assert(pfn_glProgramUniformMatrix4fv);
  pfn_glProgramUniformMatrix4fv(program,location,count,transpose,value);
}
GLAPI void APIENTRY glProgramUniformMatrix2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  assert(pfn_glProgramUniformMatrix2dv);
  pfn_glProgramUniformMatrix2dv(program,location,count,transpose,value);
}
GLAPI void APIENTRY glProgramUniformMatrix3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  assert(pfn_glProgramUniformMatrix3dv);
  pfn_glProgramUniformMatrix3dv(program,location,count,transpose,value);
}
GLAPI void APIENTRY glProgramUniformMatrix4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  assert(pfn_glProgramUniformMatrix4dv);
  pfn_glProgramUniformMatrix4dv(program,location,count,transpose,value);
}
GLAPI void APIENTRY glProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  assert(pfn_glProgramUniformMatrix2x3fv);
  pfn_glProgramUniformMatrix2x3fv(program,location,count,transpose,value);
}
GLAPI void APIENTRY glProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  assert(pfn_glProgramUniformMatrix3x2fv);
  pfn_glProgramUniformMatrix3x2fv(program,location,count,transpose,value);
}
GLAPI void APIENTRY glProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  assert(pfn_glProgramUniformMatrix2x4fv);
  pfn_glProgramUniformMatrix2x4fv(program,location,count,transpose,value);
}
GLAPI void APIENTRY glProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  assert(pfn_glProgramUniformMatrix4x2fv);
  pfn_glProgramUniformMatrix4x2fv(program,location,count,transpose,value);
}
GLAPI void APIENTRY glProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  assert(pfn_glProgramUniformMatrix3x4fv);
  pfn_glProgramUniformMatrix3x4fv(program,location,count,transpose,value);
}
GLAPI void APIENTRY glProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  assert(pfn_glProgramUniformMatrix4x3fv);
  pfn_glProgramUniformMatrix4x3fv(program,location,count,transpose,value);
}
GLAPI void APIENTRY glProgramUniformMatrix2x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  assert(pfn_glProgramUniformMatrix2x3dv);
  pfn_glProgramUniformMatrix2x3dv(program,location,count,transpose,value);
}
GLAPI void APIENTRY glProgramUniformMatrix3x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  assert(pfn_glProgramUniformMatrix3x2dv);
  pfn_glProgramUniformMatrix3x2dv(program,location,count,transpose,value);
}
GLAPI void APIENTRY glProgramUniformMatrix2x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  assert(pfn_glProgramUniformMatrix2x4dv);
  pfn_glProgramUniformMatrix2x4dv(program,location,count,transpose,value);
}
GLAPI void APIENTRY glProgramUniformMatrix4x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  assert(pfn_glProgramUniformMatrix4x2dv);
  pfn_glProgramUniformMatrix4x2dv(program,location,count,transpose,value);
}
GLAPI void APIENTRY glProgramUniformMatrix3x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  assert(pfn_glProgramUniformMatrix3x4dv);
  pfn_glProgramUniformMatrix3x4dv(program,location,count,transpose,value);
}
GLAPI void APIENTRY glProgramUniformMatrix4x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble* value)
{
  assert(pfn_glProgramUniformMatrix4x3dv);
  pfn_glProgramUniformMatrix4x3dv(program,location,count,transpose,value);
}
GLAPI void APIENTRY glValidateProgramPipeline(GLuint pipeline)
{
  assert(pfn_glValidateProgramPipeline);
  pfn_glValidateProgramPipeline(pipeline);
}
GLAPI void APIENTRY glGetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
{
  assert(pfn_glGetProgramPipelineInfoLog);
  pfn_glGetProgramPipelineInfoLog(pipeline,bufSize,length,infoLog);
}
GLAPI void APIENTRY glVertexAttribL1d(GLuint index, GLdouble x)
{
  assert(pfn_glVertexAttribL1d);
  pfn_glVertexAttribL1d(index,x);
}
GLAPI void APIENTRY glVertexAttribL2d(GLuint index, GLdouble x, GLdouble y)
{
  assert(pfn_glVertexAttribL2d);
  pfn_glVertexAttribL2d(index,x,y);
}
GLAPI void APIENTRY glVertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z)
{
  assert(pfn_glVertexAttribL3d);
  pfn_glVertexAttribL3d(index,x,y,z);
}
GLAPI void APIENTRY glVertexAttribL4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
  assert(pfn_glVertexAttribL4d);
  pfn_glVertexAttribL4d(index,x,y,z,w);
}
GLAPI void APIENTRY glVertexAttribL1dv(GLuint index, const GLdouble* v)
{
  assert(pfn_glVertexAttribL1dv);
  pfn_glVertexAttribL1dv(index,v);
}
GLAPI void APIENTRY glVertexAttribL2dv(GLuint index, const GLdouble* v)
{
  assert(pfn_glVertexAttribL2dv);
  pfn_glVertexAttribL2dv(index,v);
}
GLAPI void APIENTRY glVertexAttribL3dv(GLuint index, const GLdouble* v)
{
  assert(pfn_glVertexAttribL3dv);
  pfn_glVertexAttribL3dv(index,v);
}
GLAPI void APIENTRY glVertexAttribL4dv(GLuint index, const GLdouble* v)
{
  assert(pfn_glVertexAttribL4dv);
  pfn_glVertexAttribL4dv(index,v);
}
GLAPI void APIENTRY glVertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer)
{
  assert(pfn_glVertexAttribLPointer);
  pfn_glVertexAttribLPointer(index,size,type,stride,pointer);
}
GLAPI void APIENTRY glGetVertexAttribLdv(GLuint index, GLenum pname, GLdouble* params)
{
  assert(pfn_glGetVertexAttribLdv);
  pfn_glGetVertexAttribLdv(index,pname,params);
}
GLAPI void APIENTRY glViewportArrayv(GLuint first, GLsizei count, const GLfloat* v)
{
  assert(pfn_glViewportArrayv);
  pfn_glViewportArrayv(first,count,v);
}
GLAPI void APIENTRY glViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h)
{
  assert(pfn_glViewportIndexedf);
  pfn_glViewportIndexedf(index,x,y,w,h);
}
GLAPI void APIENTRY glViewportIndexedfv(GLuint index, const GLfloat* v)
{
  assert(pfn_glViewportIndexedfv);
  pfn_glViewportIndexedfv(index,v);
}
GLAPI void APIENTRY glScissorArrayv(GLuint first, GLsizei count, const GLint* v)
{
  assert(pfn_glScissorArrayv);
  pfn_glScissorArrayv(first,count,v);
}
GLAPI void APIENTRY glScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height)
{
  assert(pfn_glScissorIndexed);
  pfn_glScissorIndexed(index,left,bottom,width,height);
}
GLAPI void APIENTRY glScissorIndexedv(GLuint index, const GLint* v)
{
  assert(pfn_glScissorIndexedv);
  pfn_glScissorIndexedv(index,v);
}
GLAPI void APIENTRY glDepthRangeArrayv(GLuint first, GLsizei count, const GLdouble* v)
{
  assert(pfn_glDepthRangeArrayv);
  pfn_glDepthRangeArrayv(first,count,v);
}
GLAPI void APIENTRY glDepthRangeIndexed(GLuint index, GLdouble n, GLdouble f)
{
  assert(pfn_glDepthRangeIndexed);
  pfn_glDepthRangeIndexed(index,n,f);
}
GLAPI void APIENTRY glGetFloati_v(GLenum target, GLuint index, GLfloat* data)
{
  assert(pfn_glGetFloati_v);
  pfn_glGetFloati_v(target,index,data);
}
GLAPI void APIENTRY glGetDoublei_v(GLenum target, GLuint index, GLdouble* data)
{
  assert(pfn_glGetDoublei_v);
  pfn_glGetDoublei_v(target,index,data);
}

int load_GL_VERSION_4_1(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glReleaseShaderCompiler = (PFNGLRELEASESHADERCOMPILERPROC)fnGetProcAddress("glReleaseShaderCompiler");
  pfn_glShaderBinary = (PFNGLSHADERBINARYPROC)fnGetProcAddress("glShaderBinary");
  pfn_glGetShaderPrecisionFormat = (PFNGLGETSHADERPRECISIONFORMATPROC)fnGetProcAddress("glGetShaderPrecisionFormat");
  pfn_glDepthRangef = (PFNGLDEPTHRANGEFPROC)fnGetProcAddress("glDepthRangef");
  pfn_glClearDepthf = (PFNGLCLEARDEPTHFPROC)fnGetProcAddress("glClearDepthf");
  pfn_glGetProgramBinary = (PFNGLGETPROGRAMBINARYPROC)fnGetProcAddress("glGetProgramBinary");
  pfn_glProgramBinary = (PFNGLPROGRAMBINARYPROC)fnGetProcAddress("glProgramBinary");
  pfn_glProgramParameteri = (PFNGLPROGRAMPARAMETERIPROC)fnGetProcAddress("glProgramParameteri");
  pfn_glUseProgramStages = (PFNGLUSEPROGRAMSTAGESPROC)fnGetProcAddress("glUseProgramStages");
  pfn_glActiveShaderProgram = (PFNGLACTIVESHADERPROGRAMPROC)fnGetProcAddress("glActiveShaderProgram");
  pfn_glCreateShaderProgramv = (PFNGLCREATESHADERPROGRAMVPROC)fnGetProcAddress("glCreateShaderProgramv");
  pfn_glBindProgramPipeline = (PFNGLBINDPROGRAMPIPELINEPROC)fnGetProcAddress("glBindProgramPipeline");
  pfn_glDeleteProgramPipelines = (PFNGLDELETEPROGRAMPIPELINESPROC)fnGetProcAddress("glDeleteProgramPipelines");
  pfn_glGenProgramPipelines = (PFNGLGENPROGRAMPIPELINESPROC)fnGetProcAddress("glGenProgramPipelines");
  pfn_glIsProgramPipeline = (PFNGLISPROGRAMPIPELINEPROC)fnGetProcAddress("glIsProgramPipeline");
  pfn_glGetProgramPipelineiv = (PFNGLGETPROGRAMPIPELINEIVPROC)fnGetProcAddress("glGetProgramPipelineiv");
  pfn_glProgramUniform1i = (PFNGLPROGRAMUNIFORM1IPROC)fnGetProcAddress("glProgramUniform1i");
  pfn_glProgramUniform1iv = (PFNGLPROGRAMUNIFORM1IVPROC)fnGetProcAddress("glProgramUniform1iv");
  pfn_glProgramUniform1f = (PFNGLPROGRAMUNIFORM1FPROC)fnGetProcAddress("glProgramUniform1f");
  pfn_glProgramUniform1fv = (PFNGLPROGRAMUNIFORM1FVPROC)fnGetProcAddress("glProgramUniform1fv");
  pfn_glProgramUniform1d = (PFNGLPROGRAMUNIFORM1DPROC)fnGetProcAddress("glProgramUniform1d");
  pfn_glProgramUniform1dv = (PFNGLPROGRAMUNIFORM1DVPROC)fnGetProcAddress("glProgramUniform1dv");
  pfn_glProgramUniform1ui = (PFNGLPROGRAMUNIFORM1UIPROC)fnGetProcAddress("glProgramUniform1ui");
  pfn_glProgramUniform1uiv = (PFNGLPROGRAMUNIFORM1UIVPROC)fnGetProcAddress("glProgramUniform1uiv");
  pfn_glProgramUniform2i = (PFNGLPROGRAMUNIFORM2IPROC)fnGetProcAddress("glProgramUniform2i");
  pfn_glProgramUniform2iv = (PFNGLPROGRAMUNIFORM2IVPROC)fnGetProcAddress("glProgramUniform2iv");
  pfn_glProgramUniform2f = (PFNGLPROGRAMUNIFORM2FPROC)fnGetProcAddress("glProgramUniform2f");
  pfn_glProgramUniform2fv = (PFNGLPROGRAMUNIFORM2FVPROC)fnGetProcAddress("glProgramUniform2fv");
  pfn_glProgramUniform2d = (PFNGLPROGRAMUNIFORM2DPROC)fnGetProcAddress("glProgramUniform2d");
  pfn_glProgramUniform2dv = (PFNGLPROGRAMUNIFORM2DVPROC)fnGetProcAddress("glProgramUniform2dv");
  pfn_glProgramUniform2ui = (PFNGLPROGRAMUNIFORM2UIPROC)fnGetProcAddress("glProgramUniform2ui");
  pfn_glProgramUniform2uiv = (PFNGLPROGRAMUNIFORM2UIVPROC)fnGetProcAddress("glProgramUniform2uiv");
  pfn_glProgramUniform3i = (PFNGLPROGRAMUNIFORM3IPROC)fnGetProcAddress("glProgramUniform3i");
  pfn_glProgramUniform3iv = (PFNGLPROGRAMUNIFORM3IVPROC)fnGetProcAddress("glProgramUniform3iv");
  pfn_glProgramUniform3f = (PFNGLPROGRAMUNIFORM3FPROC)fnGetProcAddress("glProgramUniform3f");
  pfn_glProgramUniform3fv = (PFNGLPROGRAMUNIFORM3FVPROC)fnGetProcAddress("glProgramUniform3fv");
  pfn_glProgramUniform3d = (PFNGLPROGRAMUNIFORM3DPROC)fnGetProcAddress("glProgramUniform3d");
  pfn_glProgramUniform3dv = (PFNGLPROGRAMUNIFORM3DVPROC)fnGetProcAddress("glProgramUniform3dv");
  pfn_glProgramUniform3ui = (PFNGLPROGRAMUNIFORM3UIPROC)fnGetProcAddress("glProgramUniform3ui");
  pfn_glProgramUniform3uiv = (PFNGLPROGRAMUNIFORM3UIVPROC)fnGetProcAddress("glProgramUniform3uiv");
  pfn_glProgramUniform4i = (PFNGLPROGRAMUNIFORM4IPROC)fnGetProcAddress("glProgramUniform4i");
  pfn_glProgramUniform4iv = (PFNGLPROGRAMUNIFORM4IVPROC)fnGetProcAddress("glProgramUniform4iv");
  pfn_glProgramUniform4f = (PFNGLPROGRAMUNIFORM4FPROC)fnGetProcAddress("glProgramUniform4f");
  pfn_glProgramUniform4fv = (PFNGLPROGRAMUNIFORM4FVPROC)fnGetProcAddress("glProgramUniform4fv");
  pfn_glProgramUniform4d = (PFNGLPROGRAMUNIFORM4DPROC)fnGetProcAddress("glProgramUniform4d");
  pfn_glProgramUniform4dv = (PFNGLPROGRAMUNIFORM4DVPROC)fnGetProcAddress("glProgramUniform4dv");
  pfn_glProgramUniform4ui = (PFNGLPROGRAMUNIFORM4UIPROC)fnGetProcAddress("glProgramUniform4ui");
  pfn_glProgramUniform4uiv = (PFNGLPROGRAMUNIFORM4UIVPROC)fnGetProcAddress("glProgramUniform4uiv");
  pfn_glProgramUniformMatrix2fv = (PFNGLPROGRAMUNIFORMMATRIX2FVPROC)fnGetProcAddress("glProgramUniformMatrix2fv");
  pfn_glProgramUniformMatrix3fv = (PFNGLPROGRAMUNIFORMMATRIX3FVPROC)fnGetProcAddress("glProgramUniformMatrix3fv");
  pfn_glProgramUniformMatrix4fv = (PFNGLPROGRAMUNIFORMMATRIX4FVPROC)fnGetProcAddress("glProgramUniformMatrix4fv");
  pfn_glProgramUniformMatrix2dv = (PFNGLPROGRAMUNIFORMMATRIX2DVPROC)fnGetProcAddress("glProgramUniformMatrix2dv");
  pfn_glProgramUniformMatrix3dv = (PFNGLPROGRAMUNIFORMMATRIX3DVPROC)fnGetProcAddress("glProgramUniformMatrix3dv");
  pfn_glProgramUniformMatrix4dv = (PFNGLPROGRAMUNIFORMMATRIX4DVPROC)fnGetProcAddress("glProgramUniformMatrix4dv");
  pfn_glProgramUniformMatrix2x3fv = (PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC)fnGetProcAddress("glProgramUniformMatrix2x3fv");
  pfn_glProgramUniformMatrix3x2fv = (PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC)fnGetProcAddress("glProgramUniformMatrix3x2fv");
  pfn_glProgramUniformMatrix2x4fv = (PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC)fnGetProcAddress("glProgramUniformMatrix2x4fv");
  pfn_glProgramUniformMatrix4x2fv = (PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC)fnGetProcAddress("glProgramUniformMatrix4x2fv");
  pfn_glProgramUniformMatrix3x4fv = (PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC)fnGetProcAddress("glProgramUniformMatrix3x4fv");
  pfn_glProgramUniformMatrix4x3fv = (PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC)fnGetProcAddress("glProgramUniformMatrix4x3fv");
  pfn_glProgramUniformMatrix2x3dv = (PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC)fnGetProcAddress("glProgramUniformMatrix2x3dv");
  pfn_glProgramUniformMatrix3x2dv = (PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC)fnGetProcAddress("glProgramUniformMatrix3x2dv");
  pfn_glProgramUniformMatrix2x4dv = (PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC)fnGetProcAddress("glProgramUniformMatrix2x4dv");
  pfn_glProgramUniformMatrix4x2dv = (PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC)fnGetProcAddress("glProgramUniformMatrix4x2dv");
  pfn_glProgramUniformMatrix3x4dv = (PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC)fnGetProcAddress("glProgramUniformMatrix3x4dv");
  pfn_glProgramUniformMatrix4x3dv = (PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC)fnGetProcAddress("glProgramUniformMatrix4x3dv");
  pfn_glValidateProgramPipeline = (PFNGLVALIDATEPROGRAMPIPELINEPROC)fnGetProcAddress("glValidateProgramPipeline");
  pfn_glGetProgramPipelineInfoLog = (PFNGLGETPROGRAMPIPELINEINFOLOGPROC)fnGetProcAddress("glGetProgramPipelineInfoLog");
  pfn_glVertexAttribL1d = (PFNGLVERTEXATTRIBL1DPROC)fnGetProcAddress("glVertexAttribL1d");
  pfn_glVertexAttribL2d = (PFNGLVERTEXATTRIBL2DPROC)fnGetProcAddress("glVertexAttribL2d");
  pfn_glVertexAttribL3d = (PFNGLVERTEXATTRIBL3DPROC)fnGetProcAddress("glVertexAttribL3d");
  pfn_glVertexAttribL4d = (PFNGLVERTEXATTRIBL4DPROC)fnGetProcAddress("glVertexAttribL4d");
  pfn_glVertexAttribL1dv = (PFNGLVERTEXATTRIBL1DVPROC)fnGetProcAddress("glVertexAttribL1dv");
  pfn_glVertexAttribL2dv = (PFNGLVERTEXATTRIBL2DVPROC)fnGetProcAddress("glVertexAttribL2dv");
  pfn_glVertexAttribL3dv = (PFNGLVERTEXATTRIBL3DVPROC)fnGetProcAddress("glVertexAttribL3dv");
  pfn_glVertexAttribL4dv = (PFNGLVERTEXATTRIBL4DVPROC)fnGetProcAddress("glVertexAttribL4dv");
  pfn_glVertexAttribLPointer = (PFNGLVERTEXATTRIBLPOINTERPROC)fnGetProcAddress("glVertexAttribLPointer");
  pfn_glGetVertexAttribLdv = (PFNGLGETVERTEXATTRIBLDVPROC)fnGetProcAddress("glGetVertexAttribLdv");
  pfn_glViewportArrayv = (PFNGLVIEWPORTARRAYVPROC)fnGetProcAddress("glViewportArrayv");
  pfn_glViewportIndexedf = (PFNGLVIEWPORTINDEXEDFPROC)fnGetProcAddress("glViewportIndexedf");
  pfn_glViewportIndexedfv = (PFNGLVIEWPORTINDEXEDFVPROC)fnGetProcAddress("glViewportIndexedfv");
  pfn_glScissorArrayv = (PFNGLSCISSORARRAYVPROC)fnGetProcAddress("glScissorArrayv");
  pfn_glScissorIndexed = (PFNGLSCISSORINDEXEDPROC)fnGetProcAddress("glScissorIndexed");
  pfn_glScissorIndexedv = (PFNGLSCISSORINDEXEDVPROC)fnGetProcAddress("glScissorIndexedv");
  pfn_glDepthRangeArrayv = (PFNGLDEPTHRANGEARRAYVPROC)fnGetProcAddress("glDepthRangeArrayv");
  pfn_glDepthRangeIndexed = (PFNGLDEPTHRANGEINDEXEDPROC)fnGetProcAddress("glDepthRangeIndexed");
  pfn_glGetFloati_v = (PFNGLGETFLOATI_VPROC)fnGetProcAddress("glGetFloati_v");
  pfn_glGetDoublei_v = (PFNGLGETDOUBLEI_VPROC)fnGetProcAddress("glGetDoublei_v");
  int success = has_version(4,1);
  success = success && (pfn_glReleaseShaderCompiler != 0);
  success = success && (pfn_glShaderBinary != 0);
  success = success && (pfn_glGetShaderPrecisionFormat != 0);
  success = success && (pfn_glDepthRangef != 0);
  success = success && (pfn_glClearDepthf != 0);
  success = success && (pfn_glGetProgramBinary != 0);
  success = success && (pfn_glProgramBinary != 0);
  success = success && (pfn_glProgramParameteri != 0);
  success = success && (pfn_glUseProgramStages != 0);
  success = success && (pfn_glActiveShaderProgram != 0);
  success = success && (pfn_glCreateShaderProgramv != 0);
  success = success && (pfn_glBindProgramPipeline != 0);
  success = success && (pfn_glDeleteProgramPipelines != 0);
  success = success && (pfn_glGenProgramPipelines != 0);
  success = success && (pfn_glIsProgramPipeline != 0);
  success = success && (pfn_glGetProgramPipelineiv != 0);
  success = success && (pfn_glProgramUniform1i != 0);
  success = success && (pfn_glProgramUniform1iv != 0);
  success = success && (pfn_glProgramUniform1f != 0);
  success = success && (pfn_glProgramUniform1fv != 0);
  success = success && (pfn_glProgramUniform1d != 0);
  success = success && (pfn_glProgramUniform1dv != 0);
  success = success && (pfn_glProgramUniform1ui != 0);
  success = success && (pfn_glProgramUniform1uiv != 0);
  success = success && (pfn_glProgramUniform2i != 0);
  success = success && (pfn_glProgramUniform2iv != 0);
  success = success && (pfn_glProgramUniform2f != 0);
  success = success && (pfn_glProgramUniform2fv != 0);
  success = success && (pfn_glProgramUniform2d != 0);
  success = success && (pfn_glProgramUniform2dv != 0);
  success = success && (pfn_glProgramUniform2ui != 0);
  success = success && (pfn_glProgramUniform2uiv != 0);
  success = success && (pfn_glProgramUniform3i != 0);
  success = success && (pfn_glProgramUniform3iv != 0);
  success = success && (pfn_glProgramUniform3f != 0);
  success = success && (pfn_glProgramUniform3fv != 0);
  success = success && (pfn_glProgramUniform3d != 0);
  success = success && (pfn_glProgramUniform3dv != 0);
  success = success && (pfn_glProgramUniform3ui != 0);
  success = success && (pfn_glProgramUniform3uiv != 0);
  success = success && (pfn_glProgramUniform4i != 0);
  success = success && (pfn_glProgramUniform4iv != 0);
  success = success && (pfn_glProgramUniform4f != 0);
  success = success && (pfn_glProgramUniform4fv != 0);
  success = success && (pfn_glProgramUniform4d != 0);
  success = success && (pfn_glProgramUniform4dv != 0);
  success = success && (pfn_glProgramUniform4ui != 0);
  success = success && (pfn_glProgramUniform4uiv != 0);
  success = success && (pfn_glProgramUniformMatrix2fv != 0);
  success = success && (pfn_glProgramUniformMatrix3fv != 0);
  success = success && (pfn_glProgramUniformMatrix4fv != 0);
  success = success && (pfn_glProgramUniformMatrix2dv != 0);
  success = success && (pfn_glProgramUniformMatrix3dv != 0);
  success = success && (pfn_glProgramUniformMatrix4dv != 0);
  success = success && (pfn_glProgramUniformMatrix2x3fv != 0);
  success = success && (pfn_glProgramUniformMatrix3x2fv != 0);
  success = success && (pfn_glProgramUniformMatrix2x4fv != 0);
  success = success && (pfn_glProgramUniformMatrix4x2fv != 0);
  success = success && (pfn_glProgramUniformMatrix3x4fv != 0);
  success = success && (pfn_glProgramUniformMatrix4x3fv != 0);
  success = success && (pfn_glProgramUniformMatrix2x3dv != 0);
  success = success && (pfn_glProgramUniformMatrix3x2dv != 0);
  success = success && (pfn_glProgramUniformMatrix2x4dv != 0);
  success = success && (pfn_glProgramUniformMatrix4x2dv != 0);
  success = success && (pfn_glProgramUniformMatrix3x4dv != 0);
  success = success && (pfn_glProgramUniformMatrix4x3dv != 0);
  success = success && (pfn_glValidateProgramPipeline != 0);
  success = success && (pfn_glGetProgramPipelineInfoLog != 0);
  success = success && (pfn_glVertexAttribL1d != 0);
  success = success && (pfn_glVertexAttribL2d != 0);
  success = success && (pfn_glVertexAttribL3d != 0);
  success = success && (pfn_glVertexAttribL4d != 0);
  success = success && (pfn_glVertexAttribL1dv != 0);
  success = success && (pfn_glVertexAttribL2dv != 0);
  success = success && (pfn_glVertexAttribL3dv != 0);
  success = success && (pfn_glVertexAttribL4dv != 0);
  success = success && (pfn_glVertexAttribLPointer != 0);
  success = success && (pfn_glGetVertexAttribLdv != 0);
  success = success && (pfn_glViewportArrayv != 0);
  success = success && (pfn_glViewportIndexedf != 0);
  success = success && (pfn_glViewportIndexedfv != 0);
  success = success && (pfn_glScissorArrayv != 0);
  success = success && (pfn_glScissorIndexed != 0);
  success = success && (pfn_glScissorIndexedv != 0);
  success = success && (pfn_glDepthRangeArrayv != 0);
  success = success && (pfn_glDepthRangeIndexed != 0);
  success = success && (pfn_glGetFloati_v != 0);
  success = success && (pfn_glGetDoublei_v != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_VERSION_4_2 */

static PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC pfn_glDrawArraysInstancedBaseInstance = 0;
static PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC pfn_glDrawElementsInstancedBaseInstance = 0;
static PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC pfn_glDrawElementsInstancedBaseVertexBaseInstance = 0;
static PFNGLGETINTERNALFORMATIVPROC pfn_glGetInternalformativ = 0;
static PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC pfn_glGetActiveAtomicCounterBufferiv = 0;
static PFNGLBINDIMAGETEXTUREPROC pfn_glBindImageTexture = 0;
static PFNGLMEMORYBARRIERPROC pfn_glMemoryBarrier = 0;
static PFNGLTEXSTORAGE1DPROC pfn_glTexStorage1D = 0;
static PFNGLTEXSTORAGE2DPROC pfn_glTexStorage2D = 0;
static PFNGLTEXSTORAGE3DPROC pfn_glTexStorage3D = 0;
static PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC pfn_glDrawTransformFeedbackInstanced = 0;
static PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC pfn_glDrawTransformFeedbackStreamInstanced = 0;

GLAPI void APIENTRY glDrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance)
{
  assert(pfn_glDrawArraysInstancedBaseInstance);
  pfn_glDrawArraysInstancedBaseInstance(mode,first,count,instancecount,baseinstance);
}
GLAPI void APIENTRY glDrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount, GLuint baseinstance)
{
  assert(pfn_glDrawElementsInstancedBaseInstance);
  pfn_glDrawElementsInstancedBaseInstance(mode,count,type,indices,instancecount,baseinstance);
}
GLAPI void APIENTRY glDrawElementsInstancedBaseVertexBaseInstance(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance)
{
  assert(pfn_glDrawElementsInstancedBaseVertexBaseInstance);
  pfn_glDrawElementsInstancedBaseVertexBaseInstance(mode,count,type,indices,instancecount,basevertex,baseinstance);
}
GLAPI void APIENTRY glGetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint* params)
{
  assert(pfn_glGetInternalformativ);
  pfn_glGetInternalformativ(target,internalformat,pname,bufSize,params);
}
GLAPI void APIENTRY glGetActiveAtomicCounterBufferiv(GLuint program, GLuint bufferIndex, GLenum pname, GLint* params)
{
  assert(pfn_glGetActiveAtomicCounterBufferiv);
  pfn_glGetActiveAtomicCounterBufferiv(program,bufferIndex,pname,params);
}
GLAPI void APIENTRY glBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format)
{
  assert(pfn_glBindImageTexture);
  pfn_glBindImageTexture(unit,texture,level,layered,layer,access,format);
}
GLAPI void APIENTRY glMemoryBarrier(GLbitfield barriers)
{
  assert(pfn_glMemoryBarrier);
  pfn_glMemoryBarrier(barriers);
}
GLAPI void APIENTRY glTexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width)
{
  assert(pfn_glTexStorage1D);
  pfn_glTexStorage1D(target,levels,internalformat,width);
}
GLAPI void APIENTRY glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
  assert(pfn_glTexStorage2D);
  pfn_glTexStorage2D(target,levels,internalformat,width,height);
}
GLAPI void APIENTRY glTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
{
  assert(pfn_glTexStorage3D);
  pfn_glTexStorage3D(target,levels,internalformat,width,height,depth);
}
GLAPI void APIENTRY glDrawTransformFeedbackInstanced(GLenum mode, GLuint id, GLsizei instancecount)
{
  assert(pfn_glDrawTransformFeedbackInstanced);
  pfn_glDrawTransformFeedbackInstanced(mode,id,instancecount);
}
GLAPI void APIENTRY glDrawTransformFeedbackStreamInstanced(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount)
{
  assert(pfn_glDrawTransformFeedbackStreamInstanced);
  pfn_glDrawTransformFeedbackStreamInstanced(mode,id,stream,instancecount);
}

int load_GL_VERSION_4_2(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glDrawArraysInstancedBaseInstance = (PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC)fnGetProcAddress("glDrawArraysInstancedBaseInstance");
  pfn_glDrawElementsInstancedBaseInstance = (PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC)fnGetProcAddress("glDrawElementsInstancedBaseInstance");
  pfn_glDrawElementsInstancedBaseVertexBaseInstance = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC)fnGetProcAddress("glDrawElementsInstancedBaseVertexBaseInstance");
  pfn_glGetInternalformativ = (PFNGLGETINTERNALFORMATIVPROC)fnGetProcAddress("glGetInternalformativ");
  pfn_glGetActiveAtomicCounterBufferiv = (PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC)fnGetProcAddress("glGetActiveAtomicCounterBufferiv");
  pfn_glBindImageTexture = (PFNGLBINDIMAGETEXTUREPROC)fnGetProcAddress("glBindImageTexture");
  pfn_glMemoryBarrier = (PFNGLMEMORYBARRIERPROC)fnGetProcAddress("glMemoryBarrier");
  pfn_glTexStorage1D = (PFNGLTEXSTORAGE1DPROC)fnGetProcAddress("glTexStorage1D");
  pfn_glTexStorage2D = (PFNGLTEXSTORAGE2DPROC)fnGetProcAddress("glTexStorage2D");
  pfn_glTexStorage3D = (PFNGLTEXSTORAGE3DPROC)fnGetProcAddress("glTexStorage3D");
  pfn_glDrawTransformFeedbackInstanced = (PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC)fnGetProcAddress("glDrawTransformFeedbackInstanced");
  pfn_glDrawTransformFeedbackStreamInstanced = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC)fnGetProcAddress("glDrawTransformFeedbackStreamInstanced");
  int success = has_version(4,2);
  success = success && (pfn_glDrawArraysInstancedBaseInstance != 0);
  success = success && (pfn_glDrawElementsInstancedBaseInstance != 0);
  success = success && (pfn_glDrawElementsInstancedBaseVertexBaseInstance != 0);
  success = success && (pfn_glGetInternalformativ != 0);
  success = success && (pfn_glGetActiveAtomicCounterBufferiv != 0);
  success = success && (pfn_glBindImageTexture != 0);
  success = success && (pfn_glMemoryBarrier != 0);
  success = success && (pfn_glTexStorage1D != 0);
  success = success && (pfn_glTexStorage2D != 0);
  success = success && (pfn_glTexStorage3D != 0);
  success = success && (pfn_glDrawTransformFeedbackInstanced != 0);
  success = success && (pfn_glDrawTransformFeedbackStreamInstanced != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_VERSION_4_3 */

static PFNGLCLEARBUFFERDATAPROC pfn_glClearBufferData = 0;
static PFNGLCLEARBUFFERSUBDATAPROC pfn_glClearBufferSubData = 0;
static PFNGLDISPATCHCOMPUTEPROC pfn_glDispatchCompute = 0;
static PFNGLDISPATCHCOMPUTEINDIRECTPROC pfn_glDispatchComputeIndirect = 0;
static PFNGLCOPYIMAGESUBDATAPROC pfn_glCopyImageSubData = 0;
static PFNGLFRAMEBUFFERPARAMETERIPROC pfn_glFramebufferParameteri = 0;
static PFNGLGETFRAMEBUFFERPARAMETERIVPROC pfn_glGetFramebufferParameteriv = 0;
static PFNGLGETINTERNALFORMATI64VPROC pfn_glGetInternalformati64v = 0;
static PFNGLINVALIDATETEXSUBIMAGEPROC pfn_glInvalidateTexSubImage = 0;
static PFNGLINVALIDATETEXIMAGEPROC pfn_glInvalidateTexImage = 0;
static PFNGLINVALIDATEBUFFERSUBDATAPROC pfn_glInvalidateBufferSubData = 0;
static PFNGLINVALIDATEBUFFERDATAPROC pfn_glInvalidateBufferData = 0;
static PFNGLINVALIDATEFRAMEBUFFERPROC pfn_glInvalidateFramebuffer = 0;
static PFNGLINVALIDATESUBFRAMEBUFFERPROC pfn_glInvalidateSubFramebuffer = 0;
static PFNGLMULTIDRAWARRAYSINDIRECTPROC pfn_glMultiDrawArraysIndirect = 0;
static PFNGLMULTIDRAWELEMENTSINDIRECTPROC pfn_glMultiDrawElementsIndirect = 0;
static PFNGLGETPROGRAMINTERFACEIVPROC pfn_glGetProgramInterfaceiv = 0;
static PFNGLGETPROGRAMRESOURCEINDEXPROC pfn_glGetProgramResourceIndex = 0;
static PFNGLGETPROGRAMRESOURCENAMEPROC pfn_glGetProgramResourceName = 0;
static PFNGLGETPROGRAMRESOURCEIVPROC pfn_glGetProgramResourceiv = 0;
static PFNGLGETPROGRAMRESOURCELOCATIONPROC pfn_glGetProgramResourceLocation = 0;
static PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC pfn_glGetProgramResourceLocationIndex = 0;
static PFNGLSHADERSTORAGEBLOCKBINDINGPROC pfn_glShaderStorageBlockBinding = 0;
static PFNGLTEXBUFFERRANGEPROC pfn_glTexBufferRange = 0;
static PFNGLTEXSTORAGE2DMULTISAMPLEPROC pfn_glTexStorage2DMultisample = 0;
static PFNGLTEXSTORAGE3DMULTISAMPLEPROC pfn_glTexStorage3DMultisample = 0;
static PFNGLTEXTUREVIEWPROC pfn_glTextureView = 0;
static PFNGLBINDVERTEXBUFFERPROC pfn_glBindVertexBuffer = 0;
static PFNGLVERTEXATTRIBFORMATPROC pfn_glVertexAttribFormat = 0;
static PFNGLVERTEXATTRIBIFORMATPROC pfn_glVertexAttribIFormat = 0;
static PFNGLVERTEXATTRIBLFORMATPROC pfn_glVertexAttribLFormat = 0;
static PFNGLVERTEXATTRIBBINDINGPROC pfn_glVertexAttribBinding = 0;
static PFNGLVERTEXBINDINGDIVISORPROC pfn_glVertexBindingDivisor = 0;
static PFNGLDEBUGMESSAGECONTROLPROC pfn_glDebugMessageControl = 0;
static PFNGLDEBUGMESSAGEINSERTPROC pfn_glDebugMessageInsert = 0;
static PFNGLDEBUGMESSAGECALLBACKPROC pfn_glDebugMessageCallback = 0;
static PFNGLGETDEBUGMESSAGELOGPROC pfn_glGetDebugMessageLog = 0;
static PFNGLPUSHDEBUGGROUPPROC pfn_glPushDebugGroup = 0;
static PFNGLPOPDEBUGGROUPPROC pfn_glPopDebugGroup = 0;
static PFNGLOBJECTLABELPROC pfn_glObjectLabel = 0;
static PFNGLGETOBJECTLABELPROC pfn_glGetObjectLabel = 0;
static PFNGLOBJECTPTRLABELPROC pfn_glObjectPtrLabel = 0;
static PFNGLGETOBJECTPTRLABELPROC pfn_glGetObjectPtrLabel = 0;

GLAPI void APIENTRY glClearBufferData(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void* data)
{
  assert(pfn_glClearBufferData);
  pfn_glClearBufferData(target,internalformat,format,type,data);
}
GLAPI void APIENTRY glClearBufferSubData(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void* data)
{
  assert(pfn_glClearBufferSubData);
  pfn_glClearBufferSubData(target,internalformat,offset,size,format,type,data);
}
GLAPI void APIENTRY glDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z)
{
  assert(pfn_glDispatchCompute);
  pfn_glDispatchCompute(num_groups_x,num_groups_y,num_groups_z);
}
GLAPI void APIENTRY glDispatchComputeIndirect(GLintptr indirect)
{
  assert(pfn_glDispatchComputeIndirect);
  pfn_glDispatchComputeIndirect(indirect);
}
GLAPI void APIENTRY glCopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth)
{
  assert(pfn_glCopyImageSubData);
  pfn_glCopyImageSubData(srcName,srcTarget,srcLevel,srcX,srcY,srcZ,dstName,dstTarget,dstLevel,dstX,dstY,dstZ,srcWidth,srcHeight,srcDepth);
}
GLAPI void APIENTRY glFramebufferParameteri(GLenum target, GLenum pname, GLint param)
{
  assert(pfn_glFramebufferParameteri);
  pfn_glFramebufferParameteri(target,pname,param);
}
GLAPI void APIENTRY glGetFramebufferParameteriv(GLenum target, GLenum pname, GLint* params)
{
  assert(pfn_glGetFramebufferParameteriv);
  pfn_glGetFramebufferParameteriv(target,pname,params);
}
GLAPI void APIENTRY glGetInternalformati64v(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64* params)
{
  assert(pfn_glGetInternalformati64v);
  pfn_glGetInternalformati64v(target,internalformat,pname,bufSize,params);
}
GLAPI void APIENTRY glInvalidateTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth)
{
  assert(pfn_glInvalidateTexSubImage);
  pfn_glInvalidateTexSubImage(texture,level,xoffset,yoffset,zoffset,width,height,depth);
}
GLAPI void APIENTRY glInvalidateTexImage(GLuint texture, GLint level)
{
  assert(pfn_glInvalidateTexImage);
  pfn_glInvalidateTexImage(texture,level);
}
GLAPI void APIENTRY glInvalidateBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr length)
{
  assert(pfn_glInvalidateBufferSubData);
  pfn_glInvalidateBufferSubData(buffer,offset,length);
}
GLAPI void APIENTRY glInvalidateBufferData(GLuint buffer)
{
  assert(pfn_glInvalidateBufferData);
  pfn_glInvalidateBufferData(buffer);
}
GLAPI void APIENTRY glInvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum* attachments)
{
  assert(pfn_glInvalidateFramebuffer);
  pfn_glInvalidateFramebuffer(target,numAttachments,attachments);
}
GLAPI void APIENTRY glInvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height)
{
  assert(pfn_glInvalidateSubFramebuffer);
  pfn_glInvalidateSubFramebuffer(target,numAttachments,attachments,x,y,width,height);
}
GLAPI void APIENTRY glMultiDrawArraysIndirect(GLenum mode, const void* indirect, GLsizei drawcount, GLsizei stride)
{
  assert(pfn_glMultiDrawArraysIndirect);
  pfn_glMultiDrawArraysIndirect(mode,indirect,drawcount,stride);
}
GLAPI void APIENTRY glMultiDrawElementsIndirect(GLenum mode, GLenum type, const void* indirect, GLsizei drawcount, GLsizei stride)
{
  assert(pfn_glMultiDrawElementsIndirect);
  pfn_glMultiDrawElementsIndirect(mode,type,indirect,drawcount,stride);
}
GLAPI void APIENTRY glGetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint* params)
{
  assert(pfn_glGetProgramInterfaceiv);
  pfn_glGetProgramInterfaceiv(program,programInterface,pname,params);
}
GLAPI GLuint APIENTRY glGetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar* name)
{
  assert(pfn_glGetProgramResourceIndex);
  return pfn_glGetProgramResourceIndex(program,programInterface,name);
}
GLAPI void APIENTRY glGetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei* length, GLchar* name)
{
  assert(pfn_glGetProgramResourceName);
  pfn_glGetProgramResourceName(program,programInterface,index,bufSize,length,name);
}
GLAPI void APIENTRY glGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum* props, GLsizei bufSize, GLsizei* length, GLint* params)
{
  assert(pfn_glGetProgramResourceiv);
  pfn_glGetProgramResourceiv(program,programInterface,index,propCount,props,bufSize,length,params);
}
GLAPI GLint APIENTRY glGetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar* name)
{
  assert(pfn_glGetProgramResourceLocation);
  return pfn_glGetProgramResourceLocation(program,programInterface,name);
}
GLAPI GLint APIENTRY glGetProgramResourceLocationIndex(GLuint program, GLenum programInterface, const GLchar* name)
{
  assert(pfn_glGetProgramResourceLocationIndex);
  return pfn_glGetProgramResourceLocationIndex(program,programInterface,name);
}
GLAPI void APIENTRY glShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding)
{
  assert(pfn_glShaderStorageBlockBinding);
  pfn_glShaderStorageBlockBinding(program,storageBlockIndex,storageBlockBinding);
}
GLAPI void APIENTRY glTexBufferRange(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
  assert(pfn_glTexBufferRange);
  pfn_glTexBufferRange(target,internalformat,buffer,offset,size);
}
GLAPI void APIENTRY glTexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
  assert(pfn_glTexStorage2DMultisample);
  pfn_glTexStorage2DMultisample(target,samples,internalformat,width,height,fixedsamplelocations);
}
GLAPI void APIENTRY glTexStorage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
  assert(pfn_glTexStorage3DMultisample);
  pfn_glTexStorage3DMultisample(target,samples,internalformat,width,height,depth,fixedsamplelocations);
}
GLAPI void APIENTRY glTextureView(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers)
{
  assert(pfn_glTextureView);
  pfn_glTextureView(texture,target,origtexture,internalformat,minlevel,numlevels,minlayer,numlayers);
}
GLAPI void APIENTRY glBindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride)
{
  assert(pfn_glBindVertexBuffer);
  pfn_glBindVertexBuffer(bindingindex,buffer,offset,stride);
}
GLAPI void APIENTRY glVertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)
{
  assert(pfn_glVertexAttribFormat);
  pfn_glVertexAttribFormat(attribindex,size,type,normalized,relativeoffset);
}
GLAPI void APIENTRY glVertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
  assert(pfn_glVertexAttribIFormat);
  pfn_glVertexAttribIFormat(attribindex,size,type,relativeoffset);
}
GLAPI void APIENTRY glVertexAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
  assert(pfn_glVertexAttribLFormat);
  pfn_glVertexAttribLFormat(attribindex,size,type,relativeoffset);
}
GLAPI void APIENTRY glVertexAttribBinding(GLuint attribindex, GLuint bindingindex)
{
  assert(pfn_glVertexAttribBinding);
  pfn_glVertexAttribBinding(attribindex,bindingindex);
}
GLAPI void APIENTRY glVertexBindingDivisor(GLuint bindingindex, GLuint divisor)
{
  assert(pfn_glVertexBindingDivisor);
  pfn_glVertexBindingDivisor(bindingindex,divisor);
}
GLAPI void APIENTRY glDebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled)
{
  assert(pfn_glDebugMessageControl);
  pfn_glDebugMessageControl(source,type,severity,count,ids,enabled);
}
GLAPI void APIENTRY glDebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* buf)
{
  assert(pfn_glDebugMessageInsert);
  pfn_glDebugMessageInsert(source,type,id,severity,length,buf);
}
GLAPI void APIENTRY glDebugMessageCallback(GLDEBUGPROC callback, const void* userParam)
{
  assert(pfn_glDebugMessageCallback);
  pfn_glDebugMessageCallback(callback,userParam);
}
GLAPI GLuint APIENTRY glGetDebugMessageLog(GLuint count, GLsizei bufSize, GLenum* sources, GLenum* types, GLuint* ids, GLenum* severities, GLsizei* lengths, GLchar* messageLog)
{
  assert(pfn_glGetDebugMessageLog);
  return pfn_glGetDebugMessageLog(count,bufSize,sources,types,ids,severities,lengths,messageLog);
}
GLAPI void APIENTRY glPushDebugGroup(GLenum source, GLuint id, GLsizei length, const GLchar* message)
{
  assert(pfn_glPushDebugGroup);
  pfn_glPushDebugGroup(source,id,length,message);
}
GLAPI void APIENTRY glPopDebugGroup(void)
{
  assert(pfn_glPopDebugGroup);
  pfn_glPopDebugGroup();
}
GLAPI void APIENTRY glObjectLabel(GLenum identifier, GLuint name, GLsizei length, const GLchar* label)
{
  assert(pfn_glObjectLabel);
  pfn_glObjectLabel(identifier,name,length,label);
}
GLAPI void APIENTRY glGetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei* length, GLchar* label)
{
  assert(pfn_glGetObjectLabel);
  pfn_glGetObjectLabel(identifier,name,bufSize,length,label);
}
GLAPI void APIENTRY glObjectPtrLabel(const void* ptr, GLsizei length, const GLchar* label)
{
  assert(pfn_glObjectPtrLabel);
  pfn_glObjectPtrLabel(ptr,length,label);
}
GLAPI void APIENTRY glGetObjectPtrLabel(const void* ptr, GLsizei bufSize, GLsizei* length, GLchar* label)
{
  assert(pfn_glGetObjectPtrLabel);
  pfn_glGetObjectPtrLabel(ptr,bufSize,length,label);
}

int load_GL_VERSION_4_3(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glClearBufferData = (PFNGLCLEARBUFFERDATAPROC)fnGetProcAddress("glClearBufferData");
  pfn_glClearBufferSubData = (PFNGLCLEARBUFFERSUBDATAPROC)fnGetProcAddress("glClearBufferSubData");
  pfn_glDispatchCompute = (PFNGLDISPATCHCOMPUTEPROC)fnGetProcAddress("glDispatchCompute");
  pfn_glDispatchComputeIndirect = (PFNGLDISPATCHCOMPUTEINDIRECTPROC)fnGetProcAddress("glDispatchComputeIndirect");
  pfn_glCopyImageSubData = (PFNGLCOPYIMAGESUBDATAPROC)fnGetProcAddress("glCopyImageSubData");
  pfn_glFramebufferParameteri = (PFNGLFRAMEBUFFERPARAMETERIPROC)fnGetProcAddress("glFramebufferParameteri");
  pfn_glGetFramebufferParameteriv = (PFNGLGETFRAMEBUFFERPARAMETERIVPROC)fnGetProcAddress("glGetFramebufferParameteriv");
  pfn_glGetInternalformati64v = (PFNGLGETINTERNALFORMATI64VPROC)fnGetProcAddress("glGetInternalformati64v");
  pfn_glInvalidateTexSubImage = (PFNGLINVALIDATETEXSUBIMAGEPROC)fnGetProcAddress("glInvalidateTexSubImage");
  pfn_glInvalidateTexImage = (PFNGLINVALIDATETEXIMAGEPROC)fnGetProcAddress("glInvalidateTexImage");
  pfn_glInvalidateBufferSubData = (PFNGLINVALIDATEBUFFERSUBDATAPROC)fnGetProcAddress("glInvalidateBufferSubData");
  pfn_glInvalidateBufferData = (PFNGLINVALIDATEBUFFERDATAPROC)fnGetProcAddress("glInvalidateBufferData");
  pfn_glInvalidateFramebuffer = (PFNGLINVALIDATEFRAMEBUFFERPROC)fnGetProcAddress("glInvalidateFramebuffer");
  pfn_glInvalidateSubFramebuffer = (PFNGLINVALIDATESUBFRAMEBUFFERPROC)fnGetProcAddress("glInvalidateSubFramebuffer");
  pfn_glMultiDrawArraysIndirect = (PFNGLMULTIDRAWARRAYSINDIRECTPROC)fnGetProcAddress("glMultiDrawArraysIndirect");
  pfn_glMultiDrawElementsIndirect = (PFNGLMULTIDRAWELEMENTSINDIRECTPROC)fnGetProcAddress("glMultiDrawElementsIndirect");
  pfn_glGetProgramInterfaceiv = (PFNGLGETPROGRAMINTERFACEIVPROC)fnGetProcAddress("glGetProgramInterfaceiv");
  pfn_glGetProgramResourceIndex = (PFNGLGETPROGRAMRESOURCEINDEXPROC)fnGetProcAddress("glGetProgramResourceIndex");
  pfn_glGetProgramResourceName = (PFNGLGETPROGRAMRESOURCENAMEPROC)fnGetProcAddress("glGetProgramResourceName");
  pfn_glGetProgramResourceiv = (PFNGLGETPROGRAMRESOURCEIVPROC)fnGetProcAddress("glGetProgramResourceiv");
  pfn_glGetProgramResourceLocation = (PFNGLGETPROGRAMRESOURCELOCATIONPROC)fnGetProcAddress("glGetProgramResourceLocation");
  pfn_glGetProgramResourceLocationIndex = (PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC)fnGetProcAddress("glGetProgramResourceLocationIndex");
  pfn_glShaderStorageBlockBinding = (PFNGLSHADERSTORAGEBLOCKBINDINGPROC)fnGetProcAddress("glShaderStorageBlockBinding");
  pfn_glTexBufferRange = (PFNGLTEXBUFFERRANGEPROC)fnGetProcAddress("glTexBufferRange");
  pfn_glTexStorage2DMultisample = (PFNGLTEXSTORAGE2DMULTISAMPLEPROC)fnGetProcAddress("glTexStorage2DMultisample");
  pfn_glTexStorage3DMultisample = (PFNGLTEXSTORAGE3DMULTISAMPLEPROC)fnGetProcAddress("glTexStorage3DMultisample");
  pfn_glTextureView = (PFNGLTEXTUREVIEWPROC)fnGetProcAddress("glTextureView");
  pfn_glBindVertexBuffer = (PFNGLBINDVERTEXBUFFERPROC)fnGetProcAddress("glBindVertexBuffer");
  pfn_glVertexAttribFormat = (PFNGLVERTEXATTRIBFORMATPROC)fnGetProcAddress("glVertexAttribFormat");
  pfn_glVertexAttribIFormat = (PFNGLVERTEXATTRIBIFORMATPROC)fnGetProcAddress("glVertexAttribIFormat");
  pfn_glVertexAttribLFormat = (PFNGLVERTEXATTRIBLFORMATPROC)fnGetProcAddress("glVertexAttribLFormat");
  pfn_glVertexAttribBinding = (PFNGLVERTEXATTRIBBINDINGPROC)fnGetProcAddress("glVertexAttribBinding");
  pfn_glVertexBindingDivisor = (PFNGLVERTEXBINDINGDIVISORPROC)fnGetProcAddress("glVertexBindingDivisor");
  pfn_glDebugMessageControl = (PFNGLDEBUGMESSAGECONTROLPROC)fnGetProcAddress("glDebugMessageControl");
  pfn_glDebugMessageInsert = (PFNGLDEBUGMESSAGEINSERTPROC)fnGetProcAddress("glDebugMessageInsert");
  pfn_glDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKPROC)fnGetProcAddress("glDebugMessageCallback");
  pfn_glGetDebugMessageLog = (PFNGLGETDEBUGMESSAGELOGPROC)fnGetProcAddress("glGetDebugMessageLog");
  pfn_glPushDebugGroup = (PFNGLPUSHDEBUGGROUPPROC)fnGetProcAddress("glPushDebugGroup");
  pfn_glPopDebugGroup = (PFNGLPOPDEBUGGROUPPROC)fnGetProcAddress("glPopDebugGroup");
  pfn_glObjectLabel = (PFNGLOBJECTLABELPROC)fnGetProcAddress("glObjectLabel");
  pfn_glGetObjectLabel = (PFNGLGETOBJECTLABELPROC)fnGetProcAddress("glGetObjectLabel");
  pfn_glObjectPtrLabel = (PFNGLOBJECTPTRLABELPROC)fnGetProcAddress("glObjectPtrLabel");
  pfn_glGetObjectPtrLabel = (PFNGLGETOBJECTPTRLABELPROC)fnGetProcAddress("glGetObjectPtrLabel");
  int success = has_version(4,3);
  success = success && (pfn_glClearBufferData != 0);
  success = success && (pfn_glClearBufferSubData != 0);
  success = success && (pfn_glDispatchCompute != 0);
  success = success && (pfn_glDispatchComputeIndirect != 0);
  success = success && (pfn_glCopyImageSubData != 0);
  success = success && (pfn_glFramebufferParameteri != 0);
  success = success && (pfn_glGetFramebufferParameteriv != 0);
  success = success && (pfn_glGetInternalformati64v != 0);
  success = success && (pfn_glInvalidateTexSubImage != 0);
  success = success && (pfn_glInvalidateTexImage != 0);
  success = success && (pfn_glInvalidateBufferSubData != 0);
  success = success && (pfn_glInvalidateBufferData != 0);
  success = success && (pfn_glInvalidateFramebuffer != 0);
  success = success && (pfn_glInvalidateSubFramebuffer != 0);
  success = success && (pfn_glMultiDrawArraysIndirect != 0);
  success = success && (pfn_glMultiDrawElementsIndirect != 0);
  success = success && (pfn_glGetProgramInterfaceiv != 0);
  success = success && (pfn_glGetProgramResourceIndex != 0);
  success = success && (pfn_glGetProgramResourceName != 0);
  success = success && (pfn_glGetProgramResourceiv != 0);
  success = success && (pfn_glGetProgramResourceLocation != 0);
  success = success && (pfn_glGetProgramResourceLocationIndex != 0);
  success = success && (pfn_glShaderStorageBlockBinding != 0);
  success = success && (pfn_glTexBufferRange != 0);
  success = success && (pfn_glTexStorage2DMultisample != 0);
  success = success && (pfn_glTexStorage3DMultisample != 0);
  success = success && (pfn_glTextureView != 0);
  success = success && (pfn_glBindVertexBuffer != 0);
  success = success && (pfn_glVertexAttribFormat != 0);
  success = success && (pfn_glVertexAttribIFormat != 0);
  success = success && (pfn_glVertexAttribLFormat != 0);
  success = success && (pfn_glVertexAttribBinding != 0);
  success = success && (pfn_glVertexBindingDivisor != 0);
  success = success && (pfn_glDebugMessageControl != 0);
  success = success && (pfn_glDebugMessageInsert != 0);
  success = success && (pfn_glDebugMessageCallback != 0);
  success = success && (pfn_glGetDebugMessageLog != 0);
  success = success && (pfn_glPushDebugGroup != 0);
  success = success && (pfn_glPopDebugGroup != 0);
  success = success && (pfn_glObjectLabel != 0);
  success = success && (pfn_glGetObjectLabel != 0);
  success = success && (pfn_glObjectPtrLabel != 0);
  success = success && (pfn_glGetObjectPtrLabel != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_VERSION_4_4 */

static PFNGLBUFFERSTORAGEPROC pfn_glBufferStorage = 0;
static PFNGLCLEARTEXIMAGEPROC pfn_glClearTexImage = 0;
static PFNGLCLEARTEXSUBIMAGEPROC pfn_glClearTexSubImage = 0;
static PFNGLBINDBUFFERSBASEPROC pfn_glBindBuffersBase = 0;
static PFNGLBINDBUFFERSRANGEPROC pfn_glBindBuffersRange = 0;
static PFNGLBINDTEXTURESPROC pfn_glBindTextures = 0;
static PFNGLBINDSAMPLERSPROC pfn_glBindSamplers = 0;
static PFNGLBINDIMAGETEXTURESPROC pfn_glBindImageTextures = 0;
static PFNGLBINDVERTEXBUFFERSPROC pfn_glBindVertexBuffers = 0;

GLAPI void APIENTRY glBufferStorage(GLenum target, GLsizeiptr size, const void* data, GLbitfield flags)
{
  assert(pfn_glBufferStorage);
  pfn_glBufferStorage(target,size,data,flags);
}
GLAPI void APIENTRY glClearTexImage(GLuint texture, GLint level, GLenum format, GLenum type, const void* data)
{
  assert(pfn_glClearTexImage);
  pfn_glClearTexImage(texture,level,format,type,data);
}
GLAPI void APIENTRY glClearTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* data)
{
  assert(pfn_glClearTexSubImage);
  pfn_glClearTexSubImage(texture,level,xoffset,yoffset,zoffset,width,height,depth,format,type,data);
}
GLAPI void APIENTRY glBindBuffersBase(GLenum target, GLuint first, GLsizei count, const GLuint* buffers)
{
  assert(pfn_glBindBuffersBase);
  pfn_glBindBuffersBase(target,first,count,buffers);
}
GLAPI void APIENTRY glBindBuffersRange(GLenum target, GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizeiptr* sizes)
{
  assert(pfn_glBindBuffersRange);
  pfn_glBindBuffersRange(target,first,count,buffers,offsets,sizes);
}
GLAPI void APIENTRY glBindTextures(GLuint first, GLsizei count, const GLuint* textures)
{
  assert(pfn_glBindTextures);
  pfn_glBindTextures(first,count,textures);
}
GLAPI void APIENTRY glBindSamplers(GLuint first, GLsizei count, const GLuint* samplers)
{
  assert(pfn_glBindSamplers);
  pfn_glBindSamplers(first,count,samplers);
}
GLAPI void APIENTRY glBindImageTextures(GLuint first, GLsizei count, const GLuint* textures)
{
  assert(pfn_glBindImageTextures);
  pfn_glBindImageTextures(first,count,textures);
}
GLAPI void APIENTRY glBindVertexBuffers(GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizei* strides)
{
  assert(pfn_glBindVertexBuffers);
  pfn_glBindVertexBuffers(first,count,buffers,offsets,strides);
}

int load_GL_VERSION_4_4(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glBufferStorage = (PFNGLBUFFERSTORAGEPROC)fnGetProcAddress("glBufferStorage");
  pfn_glClearTexImage = (PFNGLCLEARTEXIMAGEPROC)fnGetProcAddress("glClearTexImage");
  pfn_glClearTexSubImage = (PFNGLCLEARTEXSUBIMAGEPROC)fnGetProcAddress("glClearTexSubImage");
  pfn_glBindBuffersBase = (PFNGLBINDBUFFERSBASEPROC)fnGetProcAddress("glBindBuffersBase");
  pfn_glBindBuffersRange = (PFNGLBINDBUFFERSRANGEPROC)fnGetProcAddress("glBindBuffersRange");
  pfn_glBindTextures = (PFNGLBINDTEXTURESPROC)fnGetProcAddress("glBindTextures");
  pfn_glBindSamplers = (PFNGLBINDSAMPLERSPROC)fnGetProcAddress("glBindSamplers");
  pfn_glBindImageTextures = (PFNGLBINDIMAGETEXTURESPROC)fnGetProcAddress("glBindImageTextures");
  pfn_glBindVertexBuffers = (PFNGLBINDVERTEXBUFFERSPROC)fnGetProcAddress("glBindVertexBuffers");
  int success = has_version(4,4);
  success = success && (pfn_glBufferStorage != 0);
  success = success && (pfn_glClearTexImage != 0);
  success = success && (pfn_glClearTexSubImage != 0);
  success = success && (pfn_glBindBuffersBase != 0);
  success = success && (pfn_glBindBuffersRange != 0);
  success = success && (pfn_glBindTextures != 0);
  success = success && (pfn_glBindSamplers != 0);
  success = success && (pfn_glBindImageTextures != 0);
  success = success && (pfn_glBindVertexBuffers != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_VERSION_4_5 */

static PFNGLCLIPCONTROLPROC pfn_glClipControl = 0;
static PFNGLCREATETRANSFORMFEEDBACKSPROC pfn_glCreateTransformFeedbacks = 0;
static PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC pfn_glTransformFeedbackBufferBase = 0;
static PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC pfn_glTransformFeedbackBufferRange = 0;
static PFNGLGETTRANSFORMFEEDBACKIVPROC pfn_glGetTransformFeedbackiv = 0;
static PFNGLGETTRANSFORMFEEDBACKI_VPROC pfn_glGetTransformFeedbacki_v = 0;
static PFNGLGETTRANSFORMFEEDBACKI64_VPROC pfn_glGetTransformFeedbacki64_v = 0;
static PFNGLCREATEBUFFERSPROC pfn_glCreateBuffers = 0;
static PFNGLNAMEDBUFFERSTORAGEPROC pfn_glNamedBufferStorage = 0;
static PFNGLNAMEDBUFFERDATAPROC pfn_glNamedBufferData = 0;
static PFNGLNAMEDBUFFERSUBDATAPROC pfn_glNamedBufferSubData = 0;
static PFNGLCOPYNAMEDBUFFERSUBDATAPROC pfn_glCopyNamedBufferSubData = 0;
static PFNGLCLEARNAMEDBUFFERDATAPROC pfn_glClearNamedBufferData = 0;
static PFNGLCLEARNAMEDBUFFERSUBDATAPROC pfn_glClearNamedBufferSubData = 0;
static PFNGLMAPNAMEDBUFFERPROC pfn_glMapNamedBuffer = 0;
static PFNGLMAPNAMEDBUFFERRANGEPROC pfn_glMapNamedBufferRange = 0;
static PFNGLUNMAPNAMEDBUFFERPROC pfn_glUnmapNamedBuffer = 0;
static PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC pfn_glFlushMappedNamedBufferRange = 0;
static PFNGLGETNAMEDBUFFERPARAMETERIVPROC pfn_glGetNamedBufferParameteriv = 0;
static PFNGLGETNAMEDBUFFERPARAMETERI64VPROC pfn_glGetNamedBufferParameteri64v = 0;
static PFNGLGETNAMEDBUFFERPOINTERVPROC pfn_glGetNamedBufferPointerv = 0;
static PFNGLGETNAMEDBUFFERSUBDATAPROC pfn_glGetNamedBufferSubData = 0;
static PFNGLCREATEFRAMEBUFFERSPROC pfn_glCreateFramebuffers = 0;
static PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC pfn_glNamedFramebufferRenderbuffer = 0;
static PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC pfn_glNamedFramebufferParameteri = 0;
static PFNGLNAMEDFRAMEBUFFERTEXTUREPROC pfn_glNamedFramebufferTexture = 0;
static PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC pfn_glNamedFramebufferTextureLayer = 0;
static PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC pfn_glNamedFramebufferDrawBuffer = 0;
static PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC pfn_glNamedFramebufferDrawBuffers = 0;
static PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC pfn_glNamedFramebufferReadBuffer = 0;
static PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC pfn_glInvalidateNamedFramebufferData = 0;
static PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC pfn_glInvalidateNamedFramebufferSubData = 0;
static PFNGLCLEARNAMEDFRAMEBUFFERIVPROC pfn_glClearNamedFramebufferiv = 0;
static PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC pfn_glClearNamedFramebufferuiv = 0;
static PFNGLCLEARNAMEDFRAMEBUFFERFVPROC pfn_glClearNamedFramebufferfv = 0;
static PFNGLCLEARNAMEDFRAMEBUFFERFIPROC pfn_glClearNamedFramebufferfi = 0;
static PFNGLBLITNAMEDFRAMEBUFFERPROC pfn_glBlitNamedFramebuffer = 0;
static PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC pfn_glCheckNamedFramebufferStatus = 0;
static PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC pfn_glGetNamedFramebufferParameteriv = 0;
static PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC pfn_glGetNamedFramebufferAttachmentParameteriv = 0;
static PFNGLCREATERENDERBUFFERSPROC pfn_glCreateRenderbuffers = 0;
static PFNGLNAMEDRENDERBUFFERSTORAGEPROC pfn_glNamedRenderbufferStorage = 0;
static PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC pfn_glNamedRenderbufferStorageMultisample = 0;
static PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC pfn_glGetNamedRenderbufferParameteriv = 0;
static PFNGLCREATETEXTURESPROC pfn_glCreateTextures = 0;
static PFNGLTEXTUREBUFFERPROC pfn_glTextureBuffer = 0;
static PFNGLTEXTUREBUFFERRANGEPROC pfn_glTextureBufferRange = 0;
static PFNGLTEXTURESTORAGE1DPROC pfn_glTextureStorage1D = 0;
static PFNGLTEXTURESTORAGE2DPROC pfn_glTextureStorage2D = 0;
static PFNGLTEXTURESTORAGE3DPROC pfn_glTextureStorage3D = 0;
static PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC pfn_glTextureStorage2DMultisample = 0;
static PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC pfn_glTextureStorage3DMultisample = 0;
static PFNGLTEXTURESUBIMAGE1DPROC pfn_glTextureSubImage1D = 0;
static PFNGLTEXTURESUBIMAGE2DPROC pfn_glTextureSubImage2D = 0;
static PFNGLTEXTURESUBIMAGE3DPROC pfn_glTextureSubImage3D = 0;
static PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC pfn_glCompressedTextureSubImage1D = 0;
static PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC pfn_glCompressedTextureSubImage2D = 0;
static PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC pfn_glCompressedTextureSubImage3D = 0;
static PFNGLCOPYTEXTURESUBIMAGE1DPROC pfn_glCopyTextureSubImage1D = 0;
static PFNGLCOPYTEXTURESUBIMAGE2DPROC pfn_glCopyTextureSubImage2D = 0;
static PFNGLCOPYTEXTURESUBIMAGE3DPROC pfn_glCopyTextureSubImage3D = 0;
static PFNGLTEXTUREPARAMETERFPROC pfn_glTextureParameterf = 0;
static PFNGLTEXTUREPARAMETERFVPROC pfn_glTextureParameterfv = 0;
static PFNGLTEXTUREPARAMETERIPROC pfn_glTextureParameteri = 0;
static PFNGLTEXTUREPARAMETERIIVPROC pfn_glTextureParameterIiv = 0;
static PFNGLTEXTUREPARAMETERIUIVPROC pfn_glTextureParameterIuiv = 0;
static PFNGLTEXTUREPARAMETERIVPROC pfn_glTextureParameteriv = 0;
static PFNGLGENERATETEXTUREMIPMAPPROC pfn_glGenerateTextureMipmap = 0;
static PFNGLBINDTEXTUREUNITPROC pfn_glBindTextureUnit = 0;
static PFNGLGETTEXTUREIMAGEPROC pfn_glGetTextureImage = 0;
static PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC pfn_glGetCompressedTextureImage = 0;
static PFNGLGETTEXTURELEVELPARAMETERFVPROC pfn_glGetTextureLevelParameterfv = 0;
static PFNGLGETTEXTURELEVELPARAMETERIVPROC pfn_glGetTextureLevelParameteriv = 0;
static PFNGLGETTEXTUREPARAMETERFVPROC pfn_glGetTextureParameterfv = 0;
static PFNGLGETTEXTUREPARAMETERIIVPROC pfn_glGetTextureParameterIiv = 0;
static PFNGLGETTEXTUREPARAMETERIUIVPROC pfn_glGetTextureParameterIuiv = 0;
static PFNGLGETTEXTUREPARAMETERIVPROC pfn_glGetTextureParameteriv = 0;
static PFNGLCREATEVERTEXARRAYSPROC pfn_glCreateVertexArrays = 0;
static PFNGLDISABLEVERTEXARRAYATTRIBPROC pfn_glDisableVertexArrayAttrib = 0;
static PFNGLENABLEVERTEXARRAYATTRIBPROC pfn_glEnableVertexArrayAttrib = 0;
static PFNGLVERTEXARRAYELEMENTBUFFERPROC pfn_glVertexArrayElementBuffer = 0;
static PFNGLVERTEXARRAYVERTEXBUFFERPROC pfn_glVertexArrayVertexBuffer = 0;
static PFNGLVERTEXARRAYVERTEXBUFFERSPROC pfn_glVertexArrayVertexBuffers = 0;
static PFNGLVERTEXARRAYATTRIBBINDINGPROC pfn_glVertexArrayAttribBinding = 0;
static PFNGLVERTEXARRAYATTRIBFORMATPROC pfn_glVertexArrayAttribFormat = 0;
static PFNGLVERTEXARRAYATTRIBIFORMATPROC pfn_glVertexArrayAttribIFormat = 0;
static PFNGLVERTEXARRAYATTRIBLFORMATPROC pfn_glVertexArrayAttribLFormat = 0;
static PFNGLVERTEXARRAYBINDINGDIVISORPROC pfn_glVertexArrayBindingDivisor = 0;
static PFNGLGETVERTEXARRAYIVPROC pfn_glGetVertexArrayiv = 0;
static PFNGLGETVERTEXARRAYINDEXEDIVPROC pfn_glGetVertexArrayIndexediv = 0;
static PFNGLGETVERTEXARRAYINDEXED64IVPROC pfn_glGetVertexArrayIndexed64iv = 0;
static PFNGLCREATESAMPLERSPROC pfn_glCreateSamplers = 0;
static PFNGLCREATEPROGRAMPIPELINESPROC pfn_glCreateProgramPipelines = 0;
static PFNGLCREATEQUERIESPROC pfn_glCreateQueries = 0;
static PFNGLGETQUERYBUFFEROBJECTI64VPROC pfn_glGetQueryBufferObjecti64v = 0;
static PFNGLGETQUERYBUFFEROBJECTIVPROC pfn_glGetQueryBufferObjectiv = 0;
static PFNGLGETQUERYBUFFEROBJECTUI64VPROC pfn_glGetQueryBufferObjectui64v = 0;
static PFNGLGETQUERYBUFFEROBJECTUIVPROC pfn_glGetQueryBufferObjectuiv = 0;
static PFNGLMEMORYBARRIERBYREGIONPROC pfn_glMemoryBarrierByRegion = 0;
static PFNGLGETTEXTURESUBIMAGEPROC pfn_glGetTextureSubImage = 0;
static PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC pfn_glGetCompressedTextureSubImage = 0;
static PFNGLGETGRAPHICSRESETSTATUSPROC pfn_glGetGraphicsResetStatus = 0;
static PFNGLGETNCOMPRESSEDTEXIMAGEPROC pfn_glGetnCompressedTexImage = 0;
static PFNGLGETNTEXIMAGEPROC pfn_glGetnTexImage = 0;
static PFNGLGETNUNIFORMDVPROC pfn_glGetnUniformdv = 0;
static PFNGLGETNUNIFORMFVPROC pfn_glGetnUniformfv = 0;
static PFNGLGETNUNIFORMIVPROC pfn_glGetnUniformiv = 0;
static PFNGLGETNUNIFORMUIVPROC pfn_glGetnUniformuiv = 0;
static PFNGLREADNPIXELSPROC pfn_glReadnPixels = 0;
static PFNGLTEXTUREBARRIERPROC pfn_glTextureBarrier = 0;

GLAPI void APIENTRY glClipControl(GLenum origin, GLenum depth)
{
  assert(pfn_glClipControl);
  pfn_glClipControl(origin,depth);
}
GLAPI void APIENTRY glCreateTransformFeedbacks(GLsizei n, GLuint* ids)
{
  assert(pfn_glCreateTransformFeedbacks);
  pfn_glCreateTransformFeedbacks(n,ids);
}
GLAPI void APIENTRY glTransformFeedbackBufferBase(GLuint xfb, GLuint index, GLuint buffer)
{
  assert(pfn_glTransformFeedbackBufferBase);
  pfn_glTransformFeedbackBufferBase(xfb,index,buffer);
}
GLAPI void APIENTRY glTransformFeedbackBufferRange(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
  assert(pfn_glTransformFeedbackBufferRange);
  pfn_glTransformFeedbackBufferRange(xfb,index,buffer,offset,size);
}
GLAPI void APIENTRY glGetTransformFeedbackiv(GLuint xfb, GLenum pname, GLint* param)
{
  assert(pfn_glGetTransformFeedbackiv);
  pfn_glGetTransformFeedbackiv(xfb,pname,param);
}
GLAPI void APIENTRY glGetTransformFeedbacki_v(GLuint xfb, GLenum pname, GLuint index, GLint* param)
{
  assert(pfn_glGetTransformFeedbacki_v);
  pfn_glGetTransformFeedbacki_v(xfb,pname,index,param);
}
GLAPI void APIENTRY glGetTransformFeedbacki64_v(GLuint xfb, GLenum pname, GLuint index, GLint64* param)
{
  assert(pfn_glGetTransformFeedbacki64_v);
  pfn_glGetTransformFeedbacki64_v(xfb,pname,index,param);
}
GLAPI void APIENTRY glCreateBuffers(GLsizei n, GLuint* buffers)
{
  assert(pfn_glCreateBuffers);
  pfn_glCreateBuffers(n,buffers);
}
GLAPI void APIENTRY glNamedBufferStorage(GLuint buffer, GLsizeiptr size, const void* data, GLbitfield flags)
{
  assert(pfn_glNamedBufferStorage);
  pfn_glNamedBufferStorage(buffer,size,data,flags);
}
GLAPI void APIENTRY glNamedBufferData(GLuint buffer, GLsizeiptr size, const void* data, GLenum usage)
{
  assert(pfn_glNamedBufferData);
  pfn_glNamedBufferData(buffer,size,data,usage);
}
GLAPI void APIENTRY glNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data)
{
  assert(pfn_glNamedBufferSubData);
  pfn_glNamedBufferSubData(buffer,offset,size,data);
}
GLAPI void APIENTRY glCopyNamedBufferSubData(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
{
  assert(pfn_glCopyNamedBufferSubData);
  pfn_glCopyNamedBufferSubData(readBuffer,writeBuffer,readOffset,writeOffset,size);
}
GLAPI void APIENTRY glClearNamedBufferData(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void* data)
{
  assert(pfn_glClearNamedBufferData);
  pfn_glClearNamedBufferData(buffer,internalformat,format,type,data);
}
GLAPI void APIENTRY glClearNamedBufferSubData(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void* data)
{
  assert(pfn_glClearNamedBufferSubData);
  pfn_glClearNamedBufferSubData(buffer,internalformat,offset,size,format,type,data);
}
GLAPI void* APIENTRY glMapNamedBuffer(GLuint buffer, GLenum access)
{
  assert(pfn_glMapNamedBuffer);
  return pfn_glMapNamedBuffer(buffer,access);
}
GLAPI void* APIENTRY glMapNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access)
{
  assert(pfn_glMapNamedBufferRange);
  return pfn_glMapNamedBufferRange(buffer,offset,length,access);
}
GLAPI GLboolean APIENTRY glUnmapNamedBuffer(GLuint buffer)
{
  assert(pfn_glUnmapNamedBuffer);
  return pfn_glUnmapNamedBuffer(buffer);
}
GLAPI void APIENTRY glFlushMappedNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length)
{
  assert(pfn_glFlushMappedNamedBufferRange);
  pfn_glFlushMappedNamedBufferRange(buffer,offset,length);
}
GLAPI void APIENTRY glGetNamedBufferParameteriv(GLuint buffer, GLenum pname, GLint* params)
{
  assert(pfn_glGetNamedBufferParameteriv);
  pfn_glGetNamedBufferParameteriv(buffer,pname,params);
}
GLAPI void APIENTRY glGetNamedBufferParameteri64v(GLuint buffer, GLenum pname, GLint64* params)
{
  assert(pfn_glGetNamedBufferParameteri64v);
  pfn_glGetNamedBufferParameteri64v(buffer,pname,params);
}
GLAPI void APIENTRY glGetNamedBufferPointerv(GLuint buffer, GLenum pname, void* * params)
{
  assert(pfn_glGetNamedBufferPointerv);
  pfn_glGetNamedBufferPointerv(buffer,pname,params);
}
GLAPI void APIENTRY glGetNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, void* data)
{
  assert(pfn_glGetNamedBufferSubData);
  pfn_glGetNamedBufferSubData(buffer,offset,size,data);
}
GLAPI void APIENTRY glCreateFramebuffers(GLsizei n, GLuint* framebuffers)
{
  assert(pfn_glCreateFramebuffers);
  pfn_glCreateFramebuffers(n,framebuffers);
}
GLAPI void APIENTRY glNamedFramebufferRenderbuffer(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
  assert(pfn_glNamedFramebufferRenderbuffer);
  pfn_glNamedFramebufferRenderbuffer(framebuffer,attachment,renderbuffertarget,renderbuffer);
}
GLAPI void APIENTRY glNamedFramebufferParameteri(GLuint framebuffer, GLenum pname, GLint param)
{
  assert(pfn_glNamedFramebufferParameteri);
  pfn_glNamedFramebufferParameteri(framebuffer,pname,param);
}
GLAPI void APIENTRY glNamedFramebufferTexture(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level)
{
  assert(pfn_glNamedFramebufferTexture);
  pfn_glNamedFramebufferTexture(framebuffer,attachment,texture,level);
}
GLAPI void APIENTRY glNamedFramebufferTextureLayer(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer)
{
  assert(pfn_glNamedFramebufferTextureLayer);
  pfn_glNamedFramebufferTextureLayer(framebuffer,attachment,texture,level,layer);
}
GLAPI void APIENTRY glNamedFramebufferDrawBuffer(GLuint framebuffer, GLenum buf)
{
  assert(pfn_glNamedFramebufferDrawBuffer);
  pfn_glNamedFramebufferDrawBuffer(framebuffer,buf);
}
GLAPI void APIENTRY glNamedFramebufferDrawBuffers(GLuint framebuffer, GLsizei n, const GLenum* bufs)
{
  assert(pfn_glNamedFramebufferDrawBuffers);
  pfn_glNamedFramebufferDrawBuffers(framebuffer,n,bufs);
}
GLAPI void APIENTRY glNamedFramebufferReadBuffer(GLuint framebuffer, GLenum src)
{
  assert(pfn_glNamedFramebufferReadBuffer);
  pfn_glNamedFramebufferReadBuffer(framebuffer,src);
}
GLAPI void APIENTRY glInvalidateNamedFramebufferData(GLuint framebuffer, GLsizei numAttachments, const GLenum* attachments)
{
  assert(pfn_glInvalidateNamedFramebufferData);
  pfn_glInvalidateNamedFramebufferData(framebuffer,numAttachments,attachments);
}
GLAPI void APIENTRY glInvalidateNamedFramebufferSubData(GLuint framebuffer, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height)
{
  assert(pfn_glInvalidateNamedFramebufferSubData);
  pfn_glInvalidateNamedFramebufferSubData(framebuffer,numAttachments,attachments,x,y,width,height);
}
GLAPI void APIENTRY glClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint* value)
{
  assert(pfn_glClearNamedFramebufferiv);
  pfn_glClearNamedFramebufferiv(framebuffer,buffer,drawbuffer,value);
}
GLAPI void APIENTRY glClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint* value)
{
  assert(pfn_glClearNamedFramebufferuiv);
  pfn_glClearNamedFramebufferuiv(framebuffer,buffer,drawbuffer,value);
}
GLAPI void APIENTRY glClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat* value)
{
  assert(pfn_glClearNamedFramebufferfv);
  pfn_glClearNamedFramebufferfv(framebuffer,buffer,drawbuffer,value);
}
GLAPI void APIENTRY glClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)
{
  assert(pfn_glClearNamedFramebufferfi);
  pfn_glClearNamedFramebufferfi(framebuffer,buffer,drawbuffer,depth,stencil);
}
GLAPI void APIENTRY glBlitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
{
  assert(pfn_glBlitNamedFramebuffer);
  pfn_glBlitNamedFramebuffer(readFramebuffer,drawFramebuffer,srcX0,srcY0,srcX1,srcY1,dstX0,dstY0,dstX1,dstY1,mask,filter);
}
GLAPI GLenum APIENTRY glCheckNamedFramebufferStatus(GLuint framebuffer, GLenum target)
{
  assert(pfn_glCheckNamedFramebufferStatus);
  return pfn_glCheckNamedFramebufferStatus(framebuffer,target);
}
GLAPI void APIENTRY glGetNamedFramebufferParameteriv(GLuint framebuffer, GLenum pname, GLint* param)
{
  assert(pfn_glGetNamedFramebufferParameteriv);
  pfn_glGetNamedFramebufferParameteriv(framebuffer,pname,param);
}
GLAPI void APIENTRY glGetNamedFramebufferAttachmentParameteriv(GLuint framebuffer, GLenum attachment, GLenum pname, GLint* params)
{
  assert(pfn_glGetNamedFramebufferAttachmentParameteriv);
  pfn_glGetNamedFramebufferAttachmentParameteriv(framebuffer,attachment,pname,params);
}
GLAPI void APIENTRY glCreateRenderbuffers(GLsizei n, GLuint* renderbuffers)
{
  assert(pfn_glCreateRenderbuffers);
  pfn_glCreateRenderbuffers(n,renderbuffers);
}
GLAPI void APIENTRY glNamedRenderbufferStorage(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height)
{
  assert(pfn_glNamedRenderbufferStorage);
  pfn_glNamedRenderbufferStorage(renderbuffer,internalformat,width,height);
}
GLAPI void APIENTRY glNamedRenderbufferStorageMultisample(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
  assert(pfn_glNamedRenderbufferStorageMultisample);
  pfn_glNamedRenderbufferStorageMultisample(renderbuffer,samples,internalformat,width,height);
}
GLAPI void APIENTRY glGetNamedRenderbufferParameteriv(GLuint renderbuffer, GLenum pname, GLint* params)
{
  assert(pfn_glGetNamedRenderbufferParameteriv);
  pfn_glGetNamedRenderbufferParameteriv(renderbuffer,pname,params);
}
GLAPI void APIENTRY glCreateTextures(GLenum target, GLsizei n, GLuint* textures)
{
  assert(pfn_glCreateTextures);
  pfn_glCreateTextures(target,n,textures);
}
GLAPI void APIENTRY glTextureBuffer(GLuint texture, GLenum internalformat, GLuint buffer)
{
  assert(pfn_glTextureBuffer);
  pfn_glTextureBuffer(texture,internalformat,buffer);
}
GLAPI void APIENTRY glTextureBufferRange(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
  assert(pfn_glTextureBufferRange);
  pfn_glTextureBufferRange(texture,internalformat,buffer,offset,size);
}
GLAPI void APIENTRY glTextureStorage1D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width)
{
  assert(pfn_glTextureStorage1D);
  pfn_glTextureStorage1D(texture,levels,internalformat,width);
}
GLAPI void APIENTRY glTextureStorage2D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
  assert(pfn_glTextureStorage2D);
  pfn_glTextureStorage2D(texture,levels,internalformat,width,height);
}
GLAPI void APIENTRY glTextureStorage3D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
{
  assert(pfn_glTextureStorage3D);
  pfn_glTextureStorage3D(texture,levels,internalformat,width,height,depth);
}
GLAPI void APIENTRY glTextureStorage2DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
  assert(pfn_glTextureStorage2DMultisample);
  pfn_glTextureStorage2DMultisample(texture,samples,internalformat,width,height,fixedsamplelocations);
}
GLAPI void APIENTRY glTextureStorage3DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
  assert(pfn_glTextureStorage3DMultisample);
  pfn_glTextureStorage3DMultisample(texture,samples,internalformat,width,height,depth,fixedsamplelocations);
}
GLAPI void APIENTRY glTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels)
{
  assert(pfn_glTextureSubImage1D);
  pfn_glTextureSubImage1D(texture,level,xoffset,width,format,type,pixels);
}
GLAPI void APIENTRY glTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels)
{
  assert(pfn_glTextureSubImage2D);
  pfn_glTextureSubImage2D(texture,level,xoffset,yoffset,width,height,format,type,pixels);
}
GLAPI void APIENTRY glTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels)
{
  assert(pfn_glTextureSubImage3D);
  pfn_glTextureSubImage3D(texture,level,xoffset,yoffset,zoffset,width,height,depth,format,type,pixels);
}
GLAPI void APIENTRY glCompressedTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data)
{
  assert(pfn_glCompressedTextureSubImage1D);
  pfn_glCompressedTextureSubImage1D(texture,level,xoffset,width,format,imageSize,data);
}
GLAPI void APIENTRY glCompressedTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data)
{
  assert(pfn_glCompressedTextureSubImage2D);
  pfn_glCompressedTextureSubImage2D(texture,level,xoffset,yoffset,width,height,format,imageSize,data);
}
GLAPI void APIENTRY glCompressedTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data)
{
  assert(pfn_glCompressedTextureSubImage3D);
  pfn_glCompressedTextureSubImage3D(texture,level,xoffset,yoffset,zoffset,width,height,depth,format,imageSize,data);
}
GLAPI void APIENTRY glCopyTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
{
  assert(pfn_glCopyTextureSubImage1D);
  pfn_glCopyTextureSubImage1D(texture,level,xoffset,x,y,width);
}
GLAPI void APIENTRY glCopyTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
  assert(pfn_glCopyTextureSubImage2D);
  pfn_glCopyTextureSubImage2D(texture,level,xoffset,yoffset,x,y,width,height);
}
GLAPI void APIENTRY glCopyTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
  assert(pfn_glCopyTextureSubImage3D);
  pfn_glCopyTextureSubImage3D(texture,level,xoffset,yoffset,zoffset,x,y,width,height);
}
GLAPI void APIENTRY glTextureParameterf(GLuint texture, GLenum pname, GLfloat param)
{
  assert(pfn_glTextureParameterf);
  pfn_glTextureParameterf(texture,pname,param);
}
GLAPI void APIENTRY glTextureParameterfv(GLuint texture, GLenum pname, const GLfloat* param)
{
  assert(pfn_glTextureParameterfv);
  pfn_glTextureParameterfv(texture,pname,param);
}
GLAPI void APIENTRY glTextureParameteri(GLuint texture, GLenum pname, GLint param)
{
  assert(pfn_glTextureParameteri);
  pfn_glTextureParameteri(texture,pname,param);
}
GLAPI void APIENTRY glTextureParameterIiv(GLuint texture, GLenum pname, const GLint* params)
{
  assert(pfn_glTextureParameterIiv);
  pfn_glTextureParameterIiv(texture,pname,params);
}
GLAPI void APIENTRY glTextureParameterIuiv(GLuint texture, GLenum pname, const GLuint* params)
{
  assert(pfn_glTextureParameterIuiv);
  pfn_glTextureParameterIuiv(texture,pname,params);
}
GLAPI void APIENTRY glTextureParameteriv(GLuint texture, GLenum pname, const GLint* param)
{
  assert(pfn_glTextureParameteriv);
  pfn_glTextureParameteriv(texture,pname,param);
}
GLAPI void APIENTRY glGenerateTextureMipmap(GLuint texture)
{
  assert(pfn_glGenerateTextureMipmap);
  pfn_glGenerateTextureMipmap(texture);
}
GLAPI void APIENTRY glBindTextureUnit(GLuint unit, GLuint texture)
{
  assert(pfn_glBindTextureUnit);
  pfn_glBindTextureUnit(unit,texture);
}
GLAPI void APIENTRY glGetTextureImage(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void* pixels)
{
  assert(pfn_glGetTextureImage);
  pfn_glGetTextureImage(texture,level,format,type,bufSize,pixels);
}
GLAPI void APIENTRY glGetCompressedTextureImage(GLuint texture, GLint level, GLsizei bufSize, void* pixels)
{
  assert(pfn_glGetCompressedTextureImage);
  pfn_glGetCompressedTextureImage(texture,level,bufSize,pixels);
}
GLAPI void APIENTRY glGetTextureLevelParameterfv(GLuint texture, GLint level, GLenum pname, GLfloat* params)
{
  assert(pfn_glGetTextureLevelParameterfv);
  pfn_glGetTextureLevelParameterfv(texture,level,pname,params);
}
GLAPI void APIENTRY glGetTextureLevelParameteriv(GLuint texture, GLint level, GLenum pname, GLint* params)
{
  assert(pfn_glGetTextureLevelParameteriv);
  pfn_glGetTextureLevelParameteriv(texture,level,pname,params);
}
GLAPI void APIENTRY glGetTextureParameterfv(GLuint texture, GLenum pname, GLfloat* params)
{
  assert(pfn_glGetTextureParameterfv);
  pfn_glGetTextureParameterfv(texture,pname,params);
}
GLAPI void APIENTRY glGetTextureParameterIiv(GLuint texture, GLenum pname, GLint* params)
{
  assert(pfn_glGetTextureParameterIiv);
  pfn_glGetTextureParameterIiv(texture,pname,params);
}
GLAPI void APIENTRY glGetTextureParameterIuiv(GLuint texture, GLenum pname, GLuint* params)
{
  assert(pfn_glGetTextureParameterIuiv);
  pfn_glGetTextureParameterIuiv(texture,pname,params);
}
GLAPI void APIENTRY glGetTextureParameteriv(GLuint texture, GLenum pname, GLint* params)
{
  assert(pfn_glGetTextureParameteriv);
  pfn_glGetTextureParameteriv(texture,pname,params);
}
GLAPI void APIENTRY glCreateVertexArrays(GLsizei n, GLuint* arrays)
{
  assert(pfn_glCreateVertexArrays);
  pfn_glCreateVertexArrays(n,arrays);
}
GLAPI void APIENTRY glDisableVertexArrayAttrib(GLuint vaobj, GLuint index)
{
  assert(pfn_glDisableVertexArrayAttrib);
  pfn_glDisableVertexArrayAttrib(vaobj,index);
}
GLAPI void APIENTRY glEnableVertexArrayAttrib(GLuint vaobj, GLuint index)
{
  assert(pfn_glEnableVertexArrayAttrib);
  pfn_glEnableVertexArrayAttrib(vaobj,index);
}
GLAPI void APIENTRY glVertexArrayElementBuffer(GLuint vaobj, GLuint buffer)
{
  assert(pfn_glVertexArrayElementBuffer);
  pfn_glVertexArrayElementBuffer(vaobj,buffer);
}
GLAPI void APIENTRY glVertexArrayVertexBuffer(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride)
{
  assert(pfn_glVertexArrayVertexBuffer);
  pfn_glVertexArrayVertexBuffer(vaobj,bindingindex,buffer,offset,stride);
}
GLAPI void APIENTRY glVertexArrayVertexBuffers(GLuint vaobj, GLuint first, GLsizei count, const GLuint* buffers, const GLintptr* offsets, const GLsizei* strides)
{
  assert(pfn_glVertexArrayVertexBuffers);
  pfn_glVertexArrayVertexBuffers(vaobj,first,count,buffers,offsets,strides);
}
GLAPI void APIENTRY glVertexArrayAttribBinding(GLuint vaobj, GLuint attribindex, GLuint bindingindex)
{
  assert(pfn_glVertexArrayAttribBinding);
  pfn_glVertexArrayAttribBinding(vaobj,attribindex,bindingindex);
}
GLAPI void APIENTRY glVertexArrayAttribFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)
{
  assert(pfn_glVertexArrayAttribFormat);
  pfn_glVertexArrayAttribFormat(vaobj,attribindex,size,type,normalized,relativeoffset);
}
GLAPI void APIENTRY glVertexArrayAttribIFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
  assert(pfn_glVertexArrayAttribIFormat);
  pfn_glVertexArrayAttribIFormat(vaobj,attribindex,size,type,relativeoffset);
}
GLAPI void APIENTRY glVertexArrayAttribLFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
  assert(pfn_glVertexArrayAttribLFormat);
  pfn_glVertexArrayAttribLFormat(vaobj,attribindex,size,type,relativeoffset);
}
GLAPI void APIENTRY glVertexArrayBindingDivisor(GLuint vaobj, GLuint bindingindex, GLuint divisor)
{
  assert(pfn_glVertexArrayBindingDivisor);
  pfn_glVertexArrayBindingDivisor(vaobj,bindingindex,divisor);
}
GLAPI void APIENTRY glGetVertexArrayiv(GLuint vaobj, GLenum pname, GLint* param)
{
  assert(pfn_glGetVertexArrayiv);
  pfn_glGetVertexArrayiv(vaobj,pname,param);
}
GLAPI void APIENTRY glGetVertexArrayIndexediv(GLuint vaobj, GLuint index, GLenum pname, GLint* param)
{
  assert(pfn_glGetVertexArrayIndexediv);
  pfn_glGetVertexArrayIndexediv(vaobj,index,pname,param);
}
GLAPI void APIENTRY glGetVertexArrayIndexed64iv(GLuint vaobj, GLuint index, GLenum pname, GLint64* param)
{
  assert(pfn_glGetVertexArrayIndexed64iv);
  pfn_glGetVertexArrayIndexed64iv(vaobj,index,pname,param);
}
GLAPI void APIENTRY glCreateSamplers(GLsizei n, GLuint* samplers)
{
  assert(pfn_glCreateSamplers);
  pfn_glCreateSamplers(n,samplers);
}
GLAPI void APIENTRY glCreateProgramPipelines(GLsizei n, GLuint* pipelines)
{
  assert(pfn_glCreateProgramPipelines);
  pfn_glCreateProgramPipelines(n,pipelines);
}
GLAPI void APIENTRY glCreateQueries(GLenum target, GLsizei n, GLuint* ids)
{
  assert(pfn_glCreateQueries);
  pfn_glCreateQueries(target,n,ids);
}
GLAPI void APIENTRY glGetQueryBufferObjecti64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
{
  assert(pfn_glGetQueryBufferObjecti64v);
  pfn_glGetQueryBufferObjecti64v(id,buffer,pname,offset);
}
GLAPI void APIENTRY glGetQueryBufferObjectiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
{
  assert(pfn_glGetQueryBufferObjectiv);
  pfn_glGetQueryBufferObjectiv(id,buffer,pname,offset);
}
GLAPI void APIENTRY glGetQueryBufferObjectui64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
{
  assert(pfn_glGetQueryBufferObjectui64v);
  pfn_glGetQueryBufferObjectui64v(id,buffer,pname,offset);
}
GLAPI void APIENTRY glGetQueryBufferObjectuiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
{
  assert(pfn_glGetQueryBufferObjectuiv);
  pfn_glGetQueryBufferObjectuiv(id,buffer,pname,offset);
}
GLAPI void APIENTRY glMemoryBarrierByRegion(GLbitfield barriers)
{
  assert(pfn_glMemoryBarrierByRegion);
  pfn_glMemoryBarrierByRegion(barriers);
}
GLAPI void APIENTRY glGetTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void* pixels)
{
  assert(pfn_glGetTextureSubImage);
  pfn_glGetTextureSubImage(texture,level,xoffset,yoffset,zoffset,width,height,depth,format,type,bufSize,pixels);
}
GLAPI void APIENTRY glGetCompressedTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void* pixels)
{
  assert(pfn_glGetCompressedTextureSubImage);
  pfn_glGetCompressedTextureSubImage(texture,level,xoffset,yoffset,zoffset,width,height,depth,bufSize,pixels);
}
GLAPI GLenum APIENTRY glGetGraphicsResetStatus(void)
{
  assert(pfn_glGetGraphicsResetStatus);
  return pfn_glGetGraphicsResetStatus();
}
GLAPI void APIENTRY glGetnCompressedTexImage(GLenum target, GLint lod, GLsizei bufSize, void* pixels)
{
  assert(pfn_glGetnCompressedTexImage);
  pfn_glGetnCompressedTexImage(target,lod,bufSize,pixels);
}
GLAPI void APIENTRY glGetnTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void* pixels)
{
  assert(pfn_glGetnTexImage);
  pfn_glGetnTexImage(target,level,format,type,bufSize,pixels);
}
GLAPI void APIENTRY glGetnUniformdv(GLuint program, GLint location, GLsizei bufSize, GLdouble* params)
{
  assert(pfn_glGetnUniformdv);
  pfn_glGetnUniformdv(program,location,bufSize,params);
}
GLAPI void APIENTRY glGetnUniformfv(GLuint program, GLint location, GLsizei bufSize, GLfloat* params)
{
  assert(pfn_glGetnUniformfv);
  pfn_glGetnUniformfv(program,location,bufSize,params);
}
GLAPI void APIENTRY glGetnUniformiv(GLuint program, GLint location, GLsizei bufSize, GLint* params)
{
  assert(pfn_glGetnUniformiv);
  pfn_glGetnUniformiv(program,location,bufSize,params);
}
GLAPI void APIENTRY glGetnUniformuiv(GLuint program, GLint location, GLsizei bufSize, GLuint* params)
{
  assert(pfn_glGetnUniformuiv);
  pfn_glGetnUniformuiv(program,location,bufSize,params);
}
GLAPI void APIENTRY glReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void* data)
{
  assert(pfn_glReadnPixels);
  pfn_glReadnPixels(x,y,width,height,format,type,bufSize,data);
}
GLAPI void APIENTRY glTextureBarrier(void)
{
  assert(pfn_glTextureBarrier);
  pfn_glTextureBarrier();
}

int load_GL_VERSION_4_5(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glClipControl = (PFNGLCLIPCONTROLPROC)fnGetProcAddress("glClipControl");
  pfn_glCreateTransformFeedbacks = (PFNGLCREATETRANSFORMFEEDBACKSPROC)fnGetProcAddress("glCreateTransformFeedbacks");
  pfn_glTransformFeedbackBufferBase = (PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC)fnGetProcAddress("glTransformFeedbackBufferBase");
  pfn_glTransformFeedbackBufferRange = (PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC)fnGetProcAddress("glTransformFeedbackBufferRange");
  pfn_glGetTransformFeedbackiv = (PFNGLGETTRANSFORMFEEDBACKIVPROC)fnGetProcAddress("glGetTransformFeedbackiv");
  pfn_glGetTransformFeedbacki_v = (PFNGLGETTRANSFORMFEEDBACKI_VPROC)fnGetProcAddress("glGetTransformFeedbacki_v");
  pfn_glGetTransformFeedbacki64_v = (PFNGLGETTRANSFORMFEEDBACKI64_VPROC)fnGetProcAddress("glGetTransformFeedbacki64_v");
  pfn_glCreateBuffers = (PFNGLCREATEBUFFERSPROC)fnGetProcAddress("glCreateBuffers");
  pfn_glNamedBufferStorage = (PFNGLNAMEDBUFFERSTORAGEPROC)fnGetProcAddress("glNamedBufferStorage");
  pfn_glNamedBufferData = (PFNGLNAMEDBUFFERDATAPROC)fnGetProcAddress("glNamedBufferData");
  pfn_glNamedBufferSubData = (PFNGLNAMEDBUFFERSUBDATAPROC)fnGetProcAddress("glNamedBufferSubData");
  pfn_glCopyNamedBufferSubData = (PFNGLCOPYNAMEDBUFFERSUBDATAPROC)fnGetProcAddress("glCopyNamedBufferSubData");
  pfn_glClearNamedBufferData = (PFNGLCLEARNAMEDBUFFERDATAPROC)fnGetProcAddress("glClearNamedBufferData");
  pfn_glClearNamedBufferSubData = (PFNGLCLEARNAMEDBUFFERSUBDATAPROC)fnGetProcAddress("glClearNamedBufferSubData");
  pfn_glMapNamedBuffer = (PFNGLMAPNAMEDBUFFERPROC)fnGetProcAddress("glMapNamedBuffer");
  pfn_glMapNamedBufferRange = (PFNGLMAPNAMEDBUFFERRANGEPROC)fnGetProcAddress("glMapNamedBufferRange");
  pfn_glUnmapNamedBuffer = (PFNGLUNMAPNAMEDBUFFERPROC)fnGetProcAddress("glUnmapNamedBuffer");
  pfn_glFlushMappedNamedBufferRange = (PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC)fnGetProcAddress("glFlushMappedNamedBufferRange");
  pfn_glGetNamedBufferParameteriv = (PFNGLGETNAMEDBUFFERPARAMETERIVPROC)fnGetProcAddress("glGetNamedBufferParameteriv");
  pfn_glGetNamedBufferParameteri64v = (PFNGLGETNAMEDBUFFERPARAMETERI64VPROC)fnGetProcAddress("glGetNamedBufferParameteri64v");
  pfn_glGetNamedBufferPointerv = (PFNGLGETNAMEDBUFFERPOINTERVPROC)fnGetProcAddress("glGetNamedBufferPointerv");
  pfn_glGetNamedBufferSubData = (PFNGLGETNAMEDBUFFERSUBDATAPROC)fnGetProcAddress("glGetNamedBufferSubData");
  pfn_glCreateFramebuffers = (PFNGLCREATEFRAMEBUFFERSPROC)fnGetProcAddress("glCreateFramebuffers");
  pfn_glNamedFramebufferRenderbuffer = (PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC)fnGetProcAddress("glNamedFramebufferRenderbuffer");
  pfn_glNamedFramebufferParameteri = (PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC)fnGetProcAddress("glNamedFramebufferParameteri");
  pfn_glNamedFramebufferTexture = (PFNGLNAMEDFRAMEBUFFERTEXTUREPROC)fnGetProcAddress("glNamedFramebufferTexture");
  pfn_glNamedFramebufferTextureLayer = (PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC)fnGetProcAddress("glNamedFramebufferTextureLayer");
  pfn_glNamedFramebufferDrawBuffer = (PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC)fnGetProcAddress("glNamedFramebufferDrawBuffer");
  pfn_glNamedFramebufferDrawBuffers = (PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC)fnGetProcAddress("glNamedFramebufferDrawBuffers");
  pfn_glNamedFramebufferReadBuffer = (PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC)fnGetProcAddress("glNamedFramebufferReadBuffer");
  pfn_glInvalidateNamedFramebufferData = (PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC)fnGetProcAddress("glInvalidateNamedFramebufferData");
  pfn_glInvalidateNamedFramebufferSubData = (PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC)fnGetProcAddress("glInvalidateNamedFramebufferSubData");
  pfn_glClearNamedFramebufferiv = (PFNGLCLEARNAMEDFRAMEBUFFERIVPROC)fnGetProcAddress("glClearNamedFramebufferiv");
  pfn_glClearNamedFramebufferuiv = (PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC)fnGetProcAddress("glClearNamedFramebufferuiv");
  pfn_glClearNamedFramebufferfv = (PFNGLCLEARNAMEDFRAMEBUFFERFVPROC)fnGetProcAddress("glClearNamedFramebufferfv");
  pfn_glClearNamedFramebufferfi = (PFNGLCLEARNAMEDFRAMEBUFFERFIPROC)fnGetProcAddress("glClearNamedFramebufferfi");
  pfn_glBlitNamedFramebuffer = (PFNGLBLITNAMEDFRAMEBUFFERPROC)fnGetProcAddress("glBlitNamedFramebuffer");
  pfn_glCheckNamedFramebufferStatus = (PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC)fnGetProcAddress("glCheckNamedFramebufferStatus");
  pfn_glGetNamedFramebufferParameteriv = (PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC)fnGetProcAddress("glGetNamedFramebufferParameteriv");
  pfn_glGetNamedFramebufferAttachmentParameteriv = (PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC)fnGetProcAddress("glGetNamedFramebufferAttachmentParameteriv");
  pfn_glCreateRenderbuffers = (PFNGLCREATERENDERBUFFERSPROC)fnGetProcAddress("glCreateRenderbuffers");
  pfn_glNamedRenderbufferStorage = (PFNGLNAMEDRENDERBUFFERSTORAGEPROC)fnGetProcAddress("glNamedRenderbufferStorage");
  pfn_glNamedRenderbufferStorageMultisample = (PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC)fnGetProcAddress("glNamedRenderbufferStorageMultisample");
  pfn_glGetNamedRenderbufferParameteriv = (PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC)fnGetProcAddress("glGetNamedRenderbufferParameteriv");
  pfn_glCreateTextures = (PFNGLCREATETEXTURESPROC)fnGetProcAddress("glCreateTextures");
  pfn_glTextureBuffer = (PFNGLTEXTUREBUFFERPROC)fnGetProcAddress("glTextureBuffer");
  pfn_glTextureBufferRange = (PFNGLTEXTUREBUFFERRANGEPROC)fnGetProcAddress("glTextureBufferRange");
  pfn_glTextureStorage1D = (PFNGLTEXTURESTORAGE1DPROC)fnGetProcAddress("glTextureStorage1D");
  pfn_glTextureStorage2D = (PFNGLTEXTURESTORAGE2DPROC)fnGetProcAddress("glTextureStorage2D");
  pfn_glTextureStorage3D = (PFNGLTEXTURESTORAGE3DPROC)fnGetProcAddress("glTextureStorage3D");
  pfn_glTextureStorage2DMultisample = (PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC)fnGetProcAddress("glTextureStorage2DMultisample");
  pfn_glTextureStorage3DMultisample = (PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC)fnGetProcAddress("glTextureStorage3DMultisample");
  pfn_glTextureSubImage1D = (PFNGLTEXTURESUBIMAGE1DPROC)fnGetProcAddress("glTextureSubImage1D");
  pfn_glTextureSubImage2D = (PFNGLTEXTURESUBIMAGE2DPROC)fnGetProcAddress("glTextureSubImage2D");
  pfn_glTextureSubImage3D = (PFNGLTEXTURESUBIMAGE3DPROC)fnGetProcAddress("glTextureSubImage3D");
  pfn_glCompressedTextureSubImage1D = (PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC)fnGetProcAddress("glCompressedTextureSubImage1D");
  pfn_glCompressedTextureSubImage2D = (PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC)fnGetProcAddress("glCompressedTextureSubImage2D");
  pfn_glCompressedTextureSubImage3D = (PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC)fnGetProcAddress("glCompressedTextureSubImage3D");
  pfn_glCopyTextureSubImage1D = (PFNGLCOPYTEXTURESUBIMAGE1DPROC)fnGetProcAddress("glCopyTextureSubImage1D");
  pfn_glCopyTextureSubImage2D = (PFNGLCOPYTEXTURESUBIMAGE2DPROC)fnGetProcAddress("glCopyTextureSubImage2D");
  pfn_glCopyTextureSubImage3D = (PFNGLCOPYTEXTURESUBIMAGE3DPROC)fnGetProcAddress("glCopyTextureSubImage3D");
  pfn_glTextureParameterf = (PFNGLTEXTUREPARAMETERFPROC)fnGetProcAddress("glTextureParameterf");
  pfn_glTextureParameterfv = (PFNGLTEXTUREPARAMETERFVPROC)fnGetProcAddress("glTextureParameterfv");
  pfn_glTextureParameteri = (PFNGLTEXTUREPARAMETERIPROC)fnGetProcAddress("glTextureParameteri");
  pfn_glTextureParameterIiv = (PFNGLTEXTUREPARAMETERIIVPROC)fnGetProcAddress("glTextureParameterIiv");
  pfn_glTextureParameterIuiv = (PFNGLTEXTUREPARAMETERIUIVPROC)fnGetProcAddress("glTextureParameterIuiv");
  pfn_glTextureParameteriv = (PFNGLTEXTUREPARAMETERIVPROC)fnGetProcAddress("glTextureParameteriv");
  pfn_glGenerateTextureMipmap = (PFNGLGENERATETEXTUREMIPMAPPROC)fnGetProcAddress("glGenerateTextureMipmap");
  pfn_glBindTextureUnit = (PFNGLBINDTEXTUREUNITPROC)fnGetProcAddress("glBindTextureUnit");
  pfn_glGetTextureImage = (PFNGLGETTEXTUREIMAGEPROC)fnGetProcAddress("glGetTextureImage");
  pfn_glGetCompressedTextureImage = (PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC)fnGetProcAddress("glGetCompressedTextureImage");
  pfn_glGetTextureLevelParameterfv = (PFNGLGETTEXTURELEVELPARAMETERFVPROC)fnGetProcAddress("glGetTextureLevelParameterfv");
  pfn_glGetTextureLevelParameteriv = (PFNGLGETTEXTURELEVELPARAMETERIVPROC)fnGetProcAddress("glGetTextureLevelParameteriv");
  pfn_glGetTextureParameterfv = (PFNGLGETTEXTUREPARAMETERFVPROC)fnGetProcAddress("glGetTextureParameterfv");
  pfn_glGetTextureParameterIiv = (PFNGLGETTEXTUREPARAMETERIIVPROC)fnGetProcAddress("glGetTextureParameterIiv");
  pfn_glGetTextureParameterIuiv = (PFNGLGETTEXTUREPARAMETERIUIVPROC)fnGetProcAddress("glGetTextureParameterIuiv");
  pfn_glGetTextureParameteriv = (PFNGLGETTEXTUREPARAMETERIVPROC)fnGetProcAddress("glGetTextureParameteriv");
  pfn_glCreateVertexArrays = (PFNGLCREATEVERTEXARRAYSPROC)fnGetProcAddress("glCreateVertexArrays");
  pfn_glDisableVertexArrayAttrib = (PFNGLDISABLEVERTEXARRAYATTRIBPROC)fnGetProcAddress("glDisableVertexArrayAttrib");
  pfn_glEnableVertexArrayAttrib = (PFNGLENABLEVERTEXARRAYATTRIBPROC)fnGetProcAddress("glEnableVertexArrayAttrib");
  pfn_glVertexArrayElementBuffer = (PFNGLVERTEXARRAYELEMENTBUFFERPROC)fnGetProcAddress("glVertexArrayElementBuffer");
  pfn_glVertexArrayVertexBuffer = (PFNGLVERTEXARRAYVERTEXBUFFERPROC)fnGetProcAddress("glVertexArrayVertexBuffer");
  pfn_glVertexArrayVertexBuffers = (PFNGLVERTEXARRAYVERTEXBUFFERSPROC)fnGetProcAddress("glVertexArrayVertexBuffers");
  pfn_glVertexArrayAttribBinding = (PFNGLVERTEXARRAYATTRIBBINDINGPROC)fnGetProcAddress("glVertexArrayAttribBinding");
  pfn_glVertexArrayAttribFormat = (PFNGLVERTEXARRAYATTRIBFORMATPROC)fnGetProcAddress("glVertexArrayAttribFormat");
  pfn_glVertexArrayAttribIFormat = (PFNGLVERTEXARRAYATTRIBIFORMATPROC)fnGetProcAddress("glVertexArrayAttribIFormat");
  pfn_glVertexArrayAttribLFormat = (PFNGLVERTEXARRAYATTRIBLFORMATPROC)fnGetProcAddress("glVertexArrayAttribLFormat");
  pfn_glVertexArrayBindingDivisor = (PFNGLVERTEXARRAYBINDINGDIVISORPROC)fnGetProcAddress("glVertexArrayBindingDivisor");
  pfn_glGetVertexArrayiv = (PFNGLGETVERTEXARRAYIVPROC)fnGetProcAddress("glGetVertexArrayiv");
  pfn_glGetVertexArrayIndexediv = (PFNGLGETVERTEXARRAYINDEXEDIVPROC)fnGetProcAddress("glGetVertexArrayIndexediv");
  pfn_glGetVertexArrayIndexed64iv = (PFNGLGETVERTEXARRAYINDEXED64IVPROC)fnGetProcAddress("glGetVertexArrayIndexed64iv");
  pfn_glCreateSamplers = (PFNGLCREATESAMPLERSPROC)fnGetProcAddress("glCreateSamplers");
  pfn_glCreateProgramPipelines = (PFNGLCREATEPROGRAMPIPELINESPROC)fnGetProcAddress("glCreateProgramPipelines");
  pfn_glCreateQueries = (PFNGLCREATEQUERIESPROC)fnGetProcAddress("glCreateQueries");
  pfn_glGetQueryBufferObjecti64v = (PFNGLGETQUERYBUFFEROBJECTI64VPROC)fnGetProcAddress("glGetQueryBufferObjecti64v");
  pfn_glGetQueryBufferObjectiv = (PFNGLGETQUERYBUFFEROBJECTIVPROC)fnGetProcAddress("glGetQueryBufferObjectiv");
  pfn_glGetQueryBufferObjectui64v = (PFNGLGETQUERYBUFFEROBJECTUI64VPROC)fnGetProcAddress("glGetQueryBufferObjectui64v");
  pfn_glGetQueryBufferObjectuiv = (PFNGLGETQUERYBUFFEROBJECTUIVPROC)fnGetProcAddress("glGetQueryBufferObjectuiv");
  pfn_glMemoryBarrierByRegion = (PFNGLMEMORYBARRIERBYREGIONPROC)fnGetProcAddress("glMemoryBarrierByRegion");
  pfn_glGetTextureSubImage = (PFNGLGETTEXTURESUBIMAGEPROC)fnGetProcAddress("glGetTextureSubImage");
  pfn_glGetCompressedTextureSubImage = (PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC)fnGetProcAddress("glGetCompressedTextureSubImage");
  pfn_glGetGraphicsResetStatus = (PFNGLGETGRAPHICSRESETSTATUSPROC)fnGetProcAddress("glGetGraphicsResetStatus");
  pfn_glGetnCompressedTexImage = (PFNGLGETNCOMPRESSEDTEXIMAGEPROC)fnGetProcAddress("glGetnCompressedTexImage");
  pfn_glGetnTexImage = (PFNGLGETNTEXIMAGEPROC)fnGetProcAddress("glGetnTexImage");
  pfn_glGetnUniformdv = (PFNGLGETNUNIFORMDVPROC)fnGetProcAddress("glGetnUniformdv");
  pfn_glGetnUniformfv = (PFNGLGETNUNIFORMFVPROC)fnGetProcAddress("glGetnUniformfv");
  pfn_glGetnUniformiv = (PFNGLGETNUNIFORMIVPROC)fnGetProcAddress("glGetnUniformiv");
  pfn_glGetnUniformuiv = (PFNGLGETNUNIFORMUIVPROC)fnGetProcAddress("glGetnUniformuiv");
  pfn_glReadnPixels = (PFNGLREADNPIXELSPROC)fnGetProcAddress("glReadnPixels");
  pfn_glTextureBarrier = (PFNGLTEXTUREBARRIERPROC)fnGetProcAddress("glTextureBarrier");
  int success = has_version(4,5);
  success = success && (pfn_glClipControl != 0);
  success = success && (pfn_glCreateTransformFeedbacks != 0);
  success = success && (pfn_glTransformFeedbackBufferBase != 0);
  success = success && (pfn_glTransformFeedbackBufferRange != 0);
  success = success && (pfn_glGetTransformFeedbackiv != 0);
  success = success && (pfn_glGetTransformFeedbacki_v != 0);
  success = success && (pfn_glGetTransformFeedbacki64_v != 0);
  success = success && (pfn_glCreateBuffers != 0);
  success = success && (pfn_glNamedBufferStorage != 0);
  success = success && (pfn_glNamedBufferData != 0);
  success = success && (pfn_glNamedBufferSubData != 0);
  success = success && (pfn_glCopyNamedBufferSubData != 0);
  success = success && (pfn_glClearNamedBufferData != 0);
  success = success && (pfn_glClearNamedBufferSubData != 0);
  success = success && (pfn_glMapNamedBuffer != 0);
  success = success && (pfn_glMapNamedBufferRange != 0);
  success = success && (pfn_glUnmapNamedBuffer != 0);
  success = success && (pfn_glFlushMappedNamedBufferRange != 0);
  success = success && (pfn_glGetNamedBufferParameteriv != 0);
  success = success && (pfn_glGetNamedBufferParameteri64v != 0);
  success = success && (pfn_glGetNamedBufferPointerv != 0);
  success = success && (pfn_glGetNamedBufferSubData != 0);
  success = success && (pfn_glCreateFramebuffers != 0);
  success = success && (pfn_glNamedFramebufferRenderbuffer != 0);
  success = success && (pfn_glNamedFramebufferParameteri != 0);
  success = success && (pfn_glNamedFramebufferTexture != 0);
  success = success && (pfn_glNamedFramebufferTextureLayer != 0);
  success = success && (pfn_glNamedFramebufferDrawBuffer != 0);
  success = success && (pfn_glNamedFramebufferDrawBuffers != 0);
  success = success && (pfn_glNamedFramebufferReadBuffer != 0);
  success = success && (pfn_glInvalidateNamedFramebufferData != 0);
  success = success && (pfn_glInvalidateNamedFramebufferSubData != 0);
  success = success && (pfn_glClearNamedFramebufferiv != 0);
  success = success && (pfn_glClearNamedFramebufferuiv != 0);
  success = success && (pfn_glClearNamedFramebufferfv != 0);
  success = success && (pfn_glClearNamedFramebufferfi != 0);
  success = success && (pfn_glBlitNamedFramebuffer != 0);
  success = success && (pfn_glCheckNamedFramebufferStatus != 0);
  success = success && (pfn_glGetNamedFramebufferParameteriv != 0);
  success = success && (pfn_glGetNamedFramebufferAttachmentParameteriv != 0);
  success = success && (pfn_glCreateRenderbuffers != 0);
  success = success && (pfn_glNamedRenderbufferStorage != 0);
  success = success && (pfn_glNamedRenderbufferStorageMultisample != 0);
  success = success && (pfn_glGetNamedRenderbufferParameteriv != 0);
  success = success && (pfn_glCreateTextures != 0);
  success = success && (pfn_glTextureBuffer != 0);
  success = success && (pfn_glTextureBufferRange != 0);
  success = success && (pfn_glTextureStorage1D != 0);
  success = success && (pfn_glTextureStorage2D != 0);
  success = success && (pfn_glTextureStorage3D != 0);
  success = success && (pfn_glTextureStorage2DMultisample != 0);
  success = success && (pfn_glTextureStorage3DMultisample != 0);
  success = success && (pfn_glTextureSubImage1D != 0);
  success = success && (pfn_glTextureSubImage2D != 0);
  success = success && (pfn_glTextureSubImage3D != 0);
  success = success && (pfn_glCompressedTextureSubImage1D != 0);
  success = success && (pfn_glCompressedTextureSubImage2D != 0);
  success = success && (pfn_glCompressedTextureSubImage3D != 0);
  success = success && (pfn_glCopyTextureSubImage1D != 0);
  success = success && (pfn_glCopyTextureSubImage2D != 0);
  success = success && (pfn_glCopyTextureSubImage3D != 0);
  success = success && (pfn_glTextureParameterf != 0);
  success = success && (pfn_glTextureParameterfv != 0);
  success = success && (pfn_glTextureParameteri != 0);
  success = success && (pfn_glTextureParameterIiv != 0);
  success = success && (pfn_glTextureParameterIuiv != 0);
  success = success && (pfn_glTextureParameteriv != 0);
  success = success && (pfn_glGenerateTextureMipmap != 0);
  success = success && (pfn_glBindTextureUnit != 0);
  success = success && (pfn_glGetTextureImage != 0);
  success = success && (pfn_glGetCompressedTextureImage != 0);
  success = success && (pfn_glGetTextureLevelParameterfv != 0);
  success = success && (pfn_glGetTextureLevelParameteriv != 0);
  success = success && (pfn_glGetTextureParameterfv != 0);
  success = success && (pfn_glGetTextureParameterIiv != 0);
  success = success && (pfn_glGetTextureParameterIuiv != 0);
  success = success && (pfn_glGetTextureParameteriv != 0);
  success = success && (pfn_glCreateVertexArrays != 0);
  success = success && (pfn_glDisableVertexArrayAttrib != 0);
  success = success && (pfn_glEnableVertexArrayAttrib != 0);
  success = success && (pfn_glVertexArrayElementBuffer != 0);
  success = success && (pfn_glVertexArrayVertexBuffer != 0);
  success = success && (pfn_glVertexArrayVertexBuffers != 0);
  success = success && (pfn_glVertexArrayAttribBinding != 0);
  success = success && (pfn_glVertexArrayAttribFormat != 0);
  success = success && (pfn_glVertexArrayAttribIFormat != 0);
  success = success && (pfn_glVertexArrayAttribLFormat != 0);
  success = success && (pfn_glVertexArrayBindingDivisor != 0);
  success = success && (pfn_glGetVertexArrayiv != 0);
  success = success && (pfn_glGetVertexArrayIndexediv != 0);
  success = success && (pfn_glGetVertexArrayIndexed64iv != 0);
  success = success && (pfn_glCreateSamplers != 0);
  success = success && (pfn_glCreateProgramPipelines != 0);
  success = success && (pfn_glCreateQueries != 0);
  success = success && (pfn_glGetQueryBufferObjecti64v != 0);
  success = success && (pfn_glGetQueryBufferObjectiv != 0);
  success = success && (pfn_glGetQueryBufferObjectui64v != 0);
  success = success && (pfn_glGetQueryBufferObjectuiv != 0);
  success = success && (pfn_glMemoryBarrierByRegion != 0);
  success = success && (pfn_glGetTextureSubImage != 0);
  success = success && (pfn_glGetCompressedTextureSubImage != 0);
  success = success && (pfn_glGetGraphicsResetStatus != 0);
  success = success && (pfn_glGetnCompressedTexImage != 0);
  success = success && (pfn_glGetnTexImage != 0);
  success = success && (pfn_glGetnUniformdv != 0);
  success = success && (pfn_glGetnUniformfv != 0);
  success = success && (pfn_glGetnUniformiv != 0);
  success = success && (pfn_glGetnUniformuiv != 0);
  success = success && (pfn_glReadnPixels != 0);
  success = success && (pfn_glTextureBarrier != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_VERSION_4_6 */

static PFNGLSPECIALIZESHADERPROC pfn_glSpecializeShader = 0;
static PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC pfn_glMultiDrawArraysIndirectCount = 0;
static PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC pfn_glMultiDrawElementsIndirectCount = 0;
static PFNGLPOLYGONOFFSETCLAMPPROC pfn_glPolygonOffsetClamp = 0;

GLAPI void APIENTRY glSpecializeShader(GLuint shader, const GLchar* pEntryPoint, GLuint numSpecializationConstants, const GLuint* pConstantIndex, const GLuint* pConstantValue)
{
  assert(pfn_glSpecializeShader);
  pfn_glSpecializeShader(shader,pEntryPoint,numSpecializationConstants,pConstantIndex,pConstantValue);
}
GLAPI void APIENTRY glMultiDrawArraysIndirectCount(GLenum mode, const void* indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride)
{
  assert(pfn_glMultiDrawArraysIndirectCount);
  pfn_glMultiDrawArraysIndirectCount(mode,indirect,drawcount,maxdrawcount,stride);
}
GLAPI void APIENTRY glMultiDrawElementsIndirectCount(GLenum mode, GLenum type, const void* indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride)
{
  assert(pfn_glMultiDrawElementsIndirectCount);
  pfn_glMultiDrawElementsIndirectCount(mode,type,indirect,drawcount,maxdrawcount,stride);
}
GLAPI void APIENTRY glPolygonOffsetClamp(GLfloat factor, GLfloat units, GLfloat clamp)
{
  assert(pfn_glPolygonOffsetClamp);
  pfn_glPolygonOffsetClamp(factor,units,clamp);
}

int load_GL_VERSION_4_6(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glSpecializeShader = (PFNGLSPECIALIZESHADERPROC)fnGetProcAddress("glSpecializeShader");
  pfn_glMultiDrawArraysIndirectCount = (PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC)fnGetProcAddress("glMultiDrawArraysIndirectCount");
  pfn_glMultiDrawElementsIndirectCount = (PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC)fnGetProcAddress("glMultiDrawElementsIndirectCount");
  pfn_glPolygonOffsetClamp = (PFNGLPOLYGONOFFSETCLAMPPROC)fnGetProcAddress("glPolygonOffsetClamp");
  int success = has_version(4,6);
  success = success && (pfn_glSpecializeShader != 0);
  success = success && (pfn_glMultiDrawArraysIndirectCount != 0);
  success = success && (pfn_glMultiDrawElementsIndirectCount != 0);
  success = success && (pfn_glPolygonOffsetClamp != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_ARB_bindless_texture */

static PFNGLGETTEXTUREHANDLEARBPROC pfn_glGetTextureHandleARB = 0;
static PFNGLGETTEXTURESAMPLERHANDLEARBPROC pfn_glGetTextureSamplerHandleARB = 0;
static PFNGLMAKETEXTUREHANDLERESIDENTARBPROC pfn_glMakeTextureHandleResidentARB = 0;
static PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC pfn_glMakeTextureHandleNonResidentARB = 0;
static PFNGLGETIMAGEHANDLEARBPROC pfn_glGetImageHandleARB = 0;
static PFNGLMAKEIMAGEHANDLERESIDENTARBPROC pfn_glMakeImageHandleResidentARB = 0;
static PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC pfn_glMakeImageHandleNonResidentARB = 0;
static PFNGLUNIFORMHANDLEUI64ARBPROC pfn_glUniformHandleui64ARB = 0;
static PFNGLUNIFORMHANDLEUI64VARBPROC pfn_glUniformHandleui64vARB = 0;
static PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC pfn_glProgramUniformHandleui64ARB = 0;
static PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC pfn_glProgramUniformHandleui64vARB = 0;
static PFNGLISTEXTUREHANDLERESIDENTARBPROC pfn_glIsTextureHandleResidentARB = 0;
static PFNGLISIMAGEHANDLERESIDENTARBPROC pfn_glIsImageHandleResidentARB = 0;
static PFNGLVERTEXATTRIBL1UI64ARBPROC pfn_glVertexAttribL1ui64ARB = 0;
static PFNGLVERTEXATTRIBL1UI64VARBPROC pfn_glVertexAttribL1ui64vARB = 0;
static PFNGLGETVERTEXATTRIBLUI64VARBPROC pfn_glGetVertexAttribLui64vARB = 0;

GLAPI GLuint64 APIENTRY glGetTextureHandleARB(GLuint texture)
{
  assert(pfn_glGetTextureHandleARB);
  return pfn_glGetTextureHandleARB(texture);
}
GLAPI GLuint64 APIENTRY glGetTextureSamplerHandleARB(GLuint texture, GLuint sampler)
{
  assert(pfn_glGetTextureSamplerHandleARB);
  return pfn_glGetTextureSamplerHandleARB(texture,sampler);
}
GLAPI void APIENTRY glMakeTextureHandleResidentARB(GLuint64 handle)
{
  assert(pfn_glMakeTextureHandleResidentARB);
  pfn_glMakeTextureHandleResidentARB(handle);
}
GLAPI void APIENTRY glMakeTextureHandleNonResidentARB(GLuint64 handle)
{
  assert(pfn_glMakeTextureHandleNonResidentARB);
  pfn_glMakeTextureHandleNonResidentARB(handle);
}
GLAPI GLuint64 APIENTRY glGetImageHandleARB(GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format)
{
  assert(pfn_glGetImageHandleARB);
  return pfn_glGetImageHandleARB(texture,level,layered,layer,format);
}
GLAPI void APIENTRY glMakeImageHandleResidentARB(GLuint64 handle, GLenum access)
{
  assert(pfn_glMakeImageHandleResidentARB);
  pfn_glMakeImageHandleResidentARB(handle,access);
}
GLAPI void APIENTRY glMakeImageHandleNonResidentARB(GLuint64 handle)
{
  assert(pfn_glMakeImageHandleNonResidentARB);
  pfn_glMakeImageHandleNonResidentARB(handle);
}
GLAPI void APIENTRY glUniformHandleui64ARB(GLint location, GLuint64 value)
{
  assert(pfn_glUniformHandleui64ARB);
  pfn_glUniformHandleui64ARB(location,value);
}
GLAPI void APIENTRY glUniformHandleui64vARB(GLint location, GLsizei count, const GLuint64* value)
{
  assert(pfn_glUniformHandleui64vARB);
  pfn_glUniformHandleui64vARB(location,count,value);
}
GLAPI void APIENTRY glProgramUniformHandleui64ARB(GLuint program, GLint location, GLuint64 value)
{
  assert(pfn_glProgramUniformHandleui64ARB);
  pfn_glProgramUniformHandleui64ARB(program,location,value);
}
GLAPI void APIENTRY glProgramUniformHandleui64vARB(GLuint program, GLint location, GLsizei count, const GLuint64* values)
{
  assert(pfn_glProgramUniformHandleui64vARB);
  pfn_glProgramUniformHandleui64vARB(program,location,count,values);
}
GLAPI GLboolean APIENTRY glIsTextureHandleResidentARB(GLuint64 handle)
{
  assert(pfn_glIsTextureHandleResidentARB);
  return pfn_glIsTextureHandleResidentARB(handle);
}
GLAPI GLboolean APIENTRY glIsImageHandleResidentARB(GLuint64 handle)
{
  assert(pfn_glIsImageHandleResidentARB);
  return pfn_glIsImageHandleResidentARB(handle);
}
GLAPI void APIENTRY glVertexAttribL1ui64ARB(GLuint index, GLuint64EXT x)
{
  assert(pfn_glVertexAttribL1ui64ARB);
  pfn_glVertexAttribL1ui64ARB(index,x);
}
GLAPI void APIENTRY glVertexAttribL1ui64vARB(GLuint index, const GLuint64EXT* v)
{
  assert(pfn_glVertexAttribL1ui64vARB);
  pfn_glVertexAttribL1ui64vARB(index,v);
}
GLAPI void APIENTRY glGetVertexAttribLui64vARB(GLuint index, GLenum pname, GLuint64EXT* params)
{
  assert(pfn_glGetVertexAttribLui64vARB);
  pfn_glGetVertexAttribLui64vARB(index,pname,params);
}

int load_GL_ARB_bindless_texture(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glGetTextureHandleARB = (PFNGLGETTEXTUREHANDLEARBPROC)fnGetProcAddress("glGetTextureHandleARB");
  pfn_glGetTextureSamplerHandleARB = (PFNGLGETTEXTURESAMPLERHANDLEARBPROC)fnGetProcAddress("glGetTextureSamplerHandleARB");
  pfn_glMakeTextureHandleResidentARB = (PFNGLMAKETEXTUREHANDLERESIDENTARBPROC)fnGetProcAddress("glMakeTextureHandleResidentARB");
  pfn_glMakeTextureHandleNonResidentARB = (PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC)fnGetProcAddress("glMakeTextureHandleNonResidentARB");
  pfn_glGetImageHandleARB = (PFNGLGETIMAGEHANDLEARBPROC)fnGetProcAddress("glGetImageHandleARB");
  pfn_glMakeImageHandleResidentARB = (PFNGLMAKEIMAGEHANDLERESIDENTARBPROC)fnGetProcAddress("glMakeImageHandleResidentARB");
  pfn_glMakeImageHandleNonResidentARB = (PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC)fnGetProcAddress("glMakeImageHandleNonResidentARB");
  pfn_glUniformHandleui64ARB = (PFNGLUNIFORMHANDLEUI64ARBPROC)fnGetProcAddress("glUniformHandleui64ARB");
  pfn_glUniformHandleui64vARB = (PFNGLUNIFORMHANDLEUI64VARBPROC)fnGetProcAddress("glUniformHandleui64vARB");
  pfn_glProgramUniformHandleui64ARB = (PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC)fnGetProcAddress("glProgramUniformHandleui64ARB");
  pfn_glProgramUniformHandleui64vARB = (PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC)fnGetProcAddress("glProgramUniformHandleui64vARB");
  pfn_glIsTextureHandleResidentARB = (PFNGLISTEXTUREHANDLERESIDENTARBPROC)fnGetProcAddress("glIsTextureHandleResidentARB");
  pfn_glIsImageHandleResidentARB = (PFNGLISIMAGEHANDLERESIDENTARBPROC)fnGetProcAddress("glIsImageHandleResidentARB");
  pfn_glVertexAttribL1ui64ARB = (PFNGLVERTEXATTRIBL1UI64ARBPROC)fnGetProcAddress("glVertexAttribL1ui64ARB");
  pfn_glVertexAttribL1ui64vARB = (PFNGLVERTEXATTRIBL1UI64VARBPROC)fnGetProcAddress("glVertexAttribL1ui64vARB");
  pfn_glGetVertexAttribLui64vARB = (PFNGLGETVERTEXATTRIBLUI64VARBPROC)fnGetProcAddress("glGetVertexAttribLui64vARB");
  int success = has_extension("GL_ARB_bindless_texture");
  success = success && (pfn_glGetTextureHandleARB != 0);
  success = success && (pfn_glGetTextureSamplerHandleARB != 0);
  success = success && (pfn_glMakeTextureHandleResidentARB != 0);
  success = success && (pfn_glMakeTextureHandleNonResidentARB != 0);
  success = success && (pfn_glGetImageHandleARB != 0);
  success = success && (pfn_glMakeImageHandleResidentARB != 0);
  success = success && (pfn_glMakeImageHandleNonResidentARB != 0);
  success = success && (pfn_glUniformHandleui64ARB != 0);
  success = success && (pfn_glUniformHandleui64vARB != 0);
  success = success && (pfn_glProgramUniformHandleui64ARB != 0);
  success = success && (pfn_glProgramUniformHandleui64vARB != 0);
  success = success && (pfn_glIsTextureHandleResidentARB != 0);
  success = success && (pfn_glIsImageHandleResidentARB != 0);
  success = success && (pfn_glVertexAttribL1ui64ARB != 0);
  success = success && (pfn_glVertexAttribL1ui64vARB != 0);
  success = success && (pfn_glGetVertexAttribLui64vARB != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_ARB_cl_event */

static PFNGLCREATESYNCFROMCLEVENTARBPROC pfn_glCreateSyncFromCLeventARB = 0;

GLAPI GLsync APIENTRY glCreateSyncFromCLeventARB(struct _cl_context* context, struct _cl_event* event, GLbitfield flags)
{
  assert(pfn_glCreateSyncFromCLeventARB);
  return pfn_glCreateSyncFromCLeventARB(context,event,flags);
}

int load_GL_ARB_cl_event(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glCreateSyncFromCLeventARB = (PFNGLCREATESYNCFROMCLEVENTARBPROC)fnGetProcAddress("glCreateSyncFromCLeventARB");
  int success = has_extension("GL_ARB_cl_event");
  success = success && (pfn_glCreateSyncFromCLeventARB != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_ARB_debug_output */

static PFNGLDEBUGMESSAGECONTROLARBPROC pfn_glDebugMessageControlARB = 0;
static PFNGLDEBUGMESSAGEINSERTARBPROC pfn_glDebugMessageInsertARB = 0;
static PFNGLDEBUGMESSAGECALLBACKARBPROC pfn_glDebugMessageCallbackARB = 0;
static PFNGLGETDEBUGMESSAGELOGARBPROC pfn_glGetDebugMessageLogARB = 0;

GLAPI void APIENTRY glDebugMessageControlARB(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled)
{
  assert(pfn_glDebugMessageControlARB);
  pfn_glDebugMessageControlARB(source,type,severity,count,ids,enabled);
}
GLAPI void APIENTRY glDebugMessageInsertARB(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* buf)
{
  assert(pfn_glDebugMessageInsertARB);
  pfn_glDebugMessageInsertARB(source,type,id,severity,length,buf);
}
GLAPI void APIENTRY glDebugMessageCallbackARB(GLDEBUGPROCARB callback, const void* userParam)
{
  assert(pfn_glDebugMessageCallbackARB);
  pfn_glDebugMessageCallbackARB(callback,userParam);
}
GLAPI GLuint APIENTRY glGetDebugMessageLogARB(GLuint count, GLsizei bufSize, GLenum* sources, GLenum* types, GLuint* ids, GLenum* severities, GLsizei* lengths, GLchar* messageLog)
{
  assert(pfn_glGetDebugMessageLogARB);
  return pfn_glGetDebugMessageLogARB(count,bufSize,sources,types,ids,severities,lengths,messageLog);
}

int load_GL_ARB_debug_output(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glDebugMessageControlARB = (PFNGLDEBUGMESSAGECONTROLARBPROC)fnGetProcAddress("glDebugMessageControlARB");
  pfn_glDebugMessageInsertARB = (PFNGLDEBUGMESSAGEINSERTARBPROC)fnGetProcAddress("glDebugMessageInsertARB");
  pfn_glDebugMessageCallbackARB = (PFNGLDEBUGMESSAGECALLBACKARBPROC)fnGetProcAddress("glDebugMessageCallbackARB");
  pfn_glGetDebugMessageLogARB = (PFNGLGETDEBUGMESSAGELOGARBPROC)fnGetProcAddress("glGetDebugMessageLogARB");
  int success = has_extension("GL_ARB_debug_output");
  success = success && (pfn_glDebugMessageControlARB != 0);
  success = success && (pfn_glDebugMessageInsertARB != 0);
  success = success && (pfn_glDebugMessageCallbackARB != 0);
  success = success && (pfn_glGetDebugMessageLogARB != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_ARB_indirect_parameters */

static PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC pfn_glMultiDrawArraysIndirectCountARB = 0;
static PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC pfn_glMultiDrawElementsIndirectCountARB = 0;

GLAPI void APIENTRY glMultiDrawArraysIndirectCountARB(GLenum mode, const void* indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride)
{
  assert(pfn_glMultiDrawArraysIndirectCountARB);
  pfn_glMultiDrawArraysIndirectCountARB(mode,indirect,drawcount,maxdrawcount,stride);
}
GLAPI void APIENTRY glMultiDrawElementsIndirectCountARB(GLenum mode, GLenum type, const void* indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride)
{
  assert(pfn_glMultiDrawElementsIndirectCountARB);
  pfn_glMultiDrawElementsIndirectCountARB(mode,type,indirect,drawcount,maxdrawcount,stride);
}

int load_GL_ARB_indirect_parameters(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glMultiDrawArraysIndirectCountARB = (PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC)fnGetProcAddress("glMultiDrawArraysIndirectCountARB");
  pfn_glMultiDrawElementsIndirectCountARB = (PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC)fnGetProcAddress("glMultiDrawElementsIndirectCountARB");
  int success = has_extension("GL_ARB_indirect_parameters");
  success = success && (pfn_glMultiDrawArraysIndirectCountARB != 0);
  success = success && (pfn_glMultiDrawElementsIndirectCountARB != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_ARB_shading_language_include */

static PFNGLNAMEDSTRINGARBPROC pfn_glNamedStringARB = 0;
static PFNGLDELETENAMEDSTRINGARBPROC pfn_glDeleteNamedStringARB = 0;
static PFNGLCOMPILESHADERINCLUDEARBPROC pfn_glCompileShaderIncludeARB = 0;
static PFNGLISNAMEDSTRINGARBPROC pfn_glIsNamedStringARB = 0;
static PFNGLGETNAMEDSTRINGARBPROC pfn_glGetNamedStringARB = 0;
static PFNGLGETNAMEDSTRINGIVARBPROC pfn_glGetNamedStringivARB = 0;

GLAPI void APIENTRY glNamedStringARB(GLenum type, GLint namelen, const GLchar* name, GLint stringlen, const GLchar* string)
{
  assert(pfn_glNamedStringARB);
  pfn_glNamedStringARB(type,namelen,name,stringlen,string);
}
GLAPI void APIENTRY glDeleteNamedStringARB(GLint namelen, const GLchar* name)
{
  assert(pfn_glDeleteNamedStringARB);
  pfn_glDeleteNamedStringARB(namelen,name);
}
GLAPI void APIENTRY glCompileShaderIncludeARB(GLuint shader, GLsizei count, const GLchar* const* path, const GLint* length)
{
  assert(pfn_glCompileShaderIncludeARB);
  pfn_glCompileShaderIncludeARB(shader,count,path,length);
}
GLAPI GLboolean APIENTRY glIsNamedStringARB(GLint namelen, const GLchar* name)
{
  assert(pfn_glIsNamedStringARB);
  return pfn_glIsNamedStringARB(namelen,name);
}
GLAPI void APIENTRY glGetNamedStringARB(GLint namelen, const GLchar* name, GLsizei bufSize, GLint* stringlen, GLchar* string)
{
  assert(pfn_glGetNamedStringARB);
  pfn_glGetNamedStringARB(namelen,name,bufSize,stringlen,string);
}
GLAPI void APIENTRY glGetNamedStringivARB(GLint namelen, const GLchar* name, GLenum pname, GLint* params)
{
  assert(pfn_glGetNamedStringivARB);
  pfn_glGetNamedStringivARB(namelen,name,pname,params);
}

int load_GL_ARB_shading_language_include(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glNamedStringARB = (PFNGLNAMEDSTRINGARBPROC)fnGetProcAddress("glNamedStringARB");
  pfn_glDeleteNamedStringARB = (PFNGLDELETENAMEDSTRINGARBPROC)fnGetProcAddress("glDeleteNamedStringARB");
  pfn_glCompileShaderIncludeARB = (PFNGLCOMPILESHADERINCLUDEARBPROC)fnGetProcAddress("glCompileShaderIncludeARB");
  pfn_glIsNamedStringARB = (PFNGLISNAMEDSTRINGARBPROC)fnGetProcAddress("glIsNamedStringARB");
  pfn_glGetNamedStringARB = (PFNGLGETNAMEDSTRINGARBPROC)fnGetProcAddress("glGetNamedStringARB");
  pfn_glGetNamedStringivARB = (PFNGLGETNAMEDSTRINGIVARBPROC)fnGetProcAddress("glGetNamedStringivARB");
  int success = has_extension("GL_ARB_shading_language_include");
  success = success && (pfn_glNamedStringARB != 0);
  success = success && (pfn_glDeleteNamedStringARB != 0);
  success = success && (pfn_glCompileShaderIncludeARB != 0);
  success = success && (pfn_glIsNamedStringARB != 0);
  success = success && (pfn_glGetNamedStringARB != 0);
  success = success && (pfn_glGetNamedStringivARB != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_ARB_texture_filter_minmax */



int load_GL_ARB_texture_filter_minmax(nvGLLoaderGetProcFN fnGetProcAddress)
{
  int success = has_extension("GL_ARB_texture_filter_minmax");
  return success;
}

/* /////////////////////////////////// */
/* GL_ARB_texture_float */



int load_GL_ARB_texture_float(nvGLLoaderGetProcFN fnGetProcAddress)
{
  int success = has_extension("GL_ARB_texture_float");
  return success;
}

/* /////////////////////////////////// */
/* GL_EXT_memory_object */

static PFNGLGETUNSIGNEDBYTEVEXTPROC pfn_glGetUnsignedBytevEXT = 0;
static PFNGLGETUNSIGNEDBYTEI_VEXTPROC pfn_glGetUnsignedBytei_vEXT = 0;
static PFNGLDELETEMEMORYOBJECTSEXTPROC pfn_glDeleteMemoryObjectsEXT = 0;
static PFNGLISMEMORYOBJECTEXTPROC pfn_glIsMemoryObjectEXT = 0;
static PFNGLCREATEMEMORYOBJECTSEXTPROC pfn_glCreateMemoryObjectsEXT = 0;
static PFNGLMEMORYOBJECTPARAMETERIVEXTPROC pfn_glMemoryObjectParameterivEXT = 0;
static PFNGLGETMEMORYOBJECTPARAMETERIVEXTPROC pfn_glGetMemoryObjectParameterivEXT = 0;
static PFNGLTEXSTORAGEMEM2DEXTPROC pfn_glTexStorageMem2DEXT = 0;
static PFNGLTEXSTORAGEMEM2DMULTISAMPLEEXTPROC pfn_glTexStorageMem2DMultisampleEXT = 0;
static PFNGLTEXSTORAGEMEM3DEXTPROC pfn_glTexStorageMem3DEXT = 0;
static PFNGLTEXSTORAGEMEM3DMULTISAMPLEEXTPROC pfn_glTexStorageMem3DMultisampleEXT = 0;
static PFNGLBUFFERSTORAGEMEMEXTPROC pfn_glBufferStorageMemEXT = 0;
static PFNGLTEXTURESTORAGEMEM2DEXTPROC pfn_glTextureStorageMem2DEXT = 0;
static PFNGLTEXTURESTORAGEMEM2DMULTISAMPLEEXTPROC pfn_glTextureStorageMem2DMultisampleEXT = 0;
static PFNGLTEXTURESTORAGEMEM3DEXTPROC pfn_glTextureStorageMem3DEXT = 0;
static PFNGLTEXTURESTORAGEMEM3DMULTISAMPLEEXTPROC pfn_glTextureStorageMem3DMultisampleEXT = 0;
static PFNGLNAMEDBUFFERSTORAGEMEMEXTPROC pfn_glNamedBufferStorageMemEXT = 0;
static PFNGLTEXSTORAGEMEM1DEXTPROC pfn_glTexStorageMem1DEXT = 0;
static PFNGLTEXTURESTORAGEMEM1DEXTPROC pfn_glTextureStorageMem1DEXT = 0;

GLAPI void APIENTRY glGetUnsignedBytevEXT(GLenum pname, GLubyte* data)
{
  assert(pfn_glGetUnsignedBytevEXT);
  pfn_glGetUnsignedBytevEXT(pname,data);
}
GLAPI void APIENTRY glGetUnsignedBytei_vEXT(GLenum target, GLuint index, GLubyte* data)
{
  assert(pfn_glGetUnsignedBytei_vEXT);
  pfn_glGetUnsignedBytei_vEXT(target,index,data);
}
GLAPI void APIENTRY glDeleteMemoryObjectsEXT(GLsizei n, const GLuint* memoryObjects)
{
  assert(pfn_glDeleteMemoryObjectsEXT);
  pfn_glDeleteMemoryObjectsEXT(n,memoryObjects);
}
GLAPI GLboolean APIENTRY glIsMemoryObjectEXT(GLuint memoryObject)
{
  assert(pfn_glIsMemoryObjectEXT);
  return pfn_glIsMemoryObjectEXT(memoryObject);
}
GLAPI void APIENTRY glCreateMemoryObjectsEXT(GLsizei n, GLuint* memoryObjects)
{
  assert(pfn_glCreateMemoryObjectsEXT);
  pfn_glCreateMemoryObjectsEXT(n,memoryObjects);
}
GLAPI void APIENTRY glMemoryObjectParameterivEXT(GLuint memoryObject, GLenum pname, const GLint* params)
{
  assert(pfn_glMemoryObjectParameterivEXT);
  pfn_glMemoryObjectParameterivEXT(memoryObject,pname,params);
}
GLAPI void APIENTRY glGetMemoryObjectParameterivEXT(GLuint memoryObject, GLenum pname, GLint* params)
{
  assert(pfn_glGetMemoryObjectParameterivEXT);
  pfn_glGetMemoryObjectParameterivEXT(memoryObject,pname,params);
}
GLAPI void APIENTRY glTexStorageMem2DEXT(GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLuint memory, GLuint64 offset)
{
  assert(pfn_glTexStorageMem2DEXT);
  pfn_glTexStorageMem2DEXT(target,levels,internalFormat,width,height,memory,offset);
}
GLAPI void APIENTRY glTexStorageMem2DMultisampleEXT(GLenum target, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset)
{
  assert(pfn_glTexStorageMem2DMultisampleEXT);
  pfn_glTexStorageMem2DMultisampleEXT(target,samples,internalFormat,width,height,fixedSampleLocations,memory,offset);
}
GLAPI void APIENTRY glTexStorageMem3DEXT(GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLuint memory, GLuint64 offset)
{
  assert(pfn_glTexStorageMem3DEXT);
  pfn_glTexStorageMem3DEXT(target,levels,internalFormat,width,height,depth,memory,offset);
}
GLAPI void APIENTRY glTexStorageMem3DMultisampleEXT(GLenum target, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset)
{
  assert(pfn_glTexStorageMem3DMultisampleEXT);
  pfn_glTexStorageMem3DMultisampleEXT(target,samples,internalFormat,width,height,depth,fixedSampleLocations,memory,offset);
}
GLAPI void APIENTRY glBufferStorageMemEXT(GLenum target, GLsizeiptr size, GLuint memory, GLuint64 offset)
{
  assert(pfn_glBufferStorageMemEXT);
  pfn_glBufferStorageMemEXT(target,size,memory,offset);
}
GLAPI void APIENTRY glTextureStorageMem2DEXT(GLuint texture, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLuint memory, GLuint64 offset)
{
  assert(pfn_glTextureStorageMem2DEXT);
  pfn_glTextureStorageMem2DEXT(texture,levels,internalFormat,width,height,memory,offset);
}
GLAPI void APIENTRY glTextureStorageMem2DMultisampleEXT(GLuint texture, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset)
{
  assert(pfn_glTextureStorageMem2DMultisampleEXT);
  pfn_glTextureStorageMem2DMultisampleEXT(texture,samples,internalFormat,width,height,fixedSampleLocations,memory,offset);
}
GLAPI void APIENTRY glTextureStorageMem3DEXT(GLuint texture, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLuint memory, GLuint64 offset)
{
  assert(pfn_glTextureStorageMem3DEXT);
  pfn_glTextureStorageMem3DEXT(texture,levels,internalFormat,width,height,depth,memory,offset);
}
GLAPI void APIENTRY glTextureStorageMem3DMultisampleEXT(GLuint texture, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations, GLuint memory, GLuint64 offset)
{
  assert(pfn_glTextureStorageMem3DMultisampleEXT);
  pfn_glTextureStorageMem3DMultisampleEXT(texture,samples,internalFormat,width,height,depth,fixedSampleLocations,memory,offset);
}
GLAPI void APIENTRY glNamedBufferStorageMemEXT(GLuint buffer, GLsizeiptr size, GLuint memory, GLuint64 offset)
{
  assert(pfn_glNamedBufferStorageMemEXT);
  pfn_glNamedBufferStorageMemEXT(buffer,size,memory,offset);
}
GLAPI void APIENTRY glTexStorageMem1DEXT(GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width, GLuint memory, GLuint64 offset)
{
  assert(pfn_glTexStorageMem1DEXT);
  pfn_glTexStorageMem1DEXT(target,levels,internalFormat,width,memory,offset);
}
GLAPI void APIENTRY glTextureStorageMem1DEXT(GLuint texture, GLsizei levels, GLenum internalFormat, GLsizei width, GLuint memory, GLuint64 offset)
{
  assert(pfn_glTextureStorageMem1DEXT);
  pfn_glTextureStorageMem1DEXT(texture,levels,internalFormat,width,memory,offset);
}

int load_GL_EXT_memory_object(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glGetUnsignedBytevEXT = (PFNGLGETUNSIGNEDBYTEVEXTPROC)fnGetProcAddress("glGetUnsignedBytevEXT");
  pfn_glGetUnsignedBytei_vEXT = (PFNGLGETUNSIGNEDBYTEI_VEXTPROC)fnGetProcAddress("glGetUnsignedBytei_vEXT");
  pfn_glDeleteMemoryObjectsEXT = (PFNGLDELETEMEMORYOBJECTSEXTPROC)fnGetProcAddress("glDeleteMemoryObjectsEXT");
  pfn_glIsMemoryObjectEXT = (PFNGLISMEMORYOBJECTEXTPROC)fnGetProcAddress("glIsMemoryObjectEXT");
  pfn_glCreateMemoryObjectsEXT = (PFNGLCREATEMEMORYOBJECTSEXTPROC)fnGetProcAddress("glCreateMemoryObjectsEXT");
  pfn_glMemoryObjectParameterivEXT = (PFNGLMEMORYOBJECTPARAMETERIVEXTPROC)fnGetProcAddress("glMemoryObjectParameterivEXT");
  pfn_glGetMemoryObjectParameterivEXT = (PFNGLGETMEMORYOBJECTPARAMETERIVEXTPROC)fnGetProcAddress("glGetMemoryObjectParameterivEXT");
  pfn_glTexStorageMem2DEXT = (PFNGLTEXSTORAGEMEM2DEXTPROC)fnGetProcAddress("glTexStorageMem2DEXT");
  pfn_glTexStorageMem2DMultisampleEXT = (PFNGLTEXSTORAGEMEM2DMULTISAMPLEEXTPROC)fnGetProcAddress("glTexStorageMem2DMultisampleEXT");
  pfn_glTexStorageMem3DEXT = (PFNGLTEXSTORAGEMEM3DEXTPROC)fnGetProcAddress("glTexStorageMem3DEXT");
  pfn_glTexStorageMem3DMultisampleEXT = (PFNGLTEXSTORAGEMEM3DMULTISAMPLEEXTPROC)fnGetProcAddress("glTexStorageMem3DMultisampleEXT");
  pfn_glBufferStorageMemEXT = (PFNGLBUFFERSTORAGEMEMEXTPROC)fnGetProcAddress("glBufferStorageMemEXT");
  pfn_glTextureStorageMem2DEXT = (PFNGLTEXTURESTORAGEMEM2DEXTPROC)fnGetProcAddress("glTextureStorageMem2DEXT");
  pfn_glTextureStorageMem2DMultisampleEXT = (PFNGLTEXTURESTORAGEMEM2DMULTISAMPLEEXTPROC)fnGetProcAddress("glTextureStorageMem2DMultisampleEXT");
  pfn_glTextureStorageMem3DEXT = (PFNGLTEXTURESTORAGEMEM3DEXTPROC)fnGetProcAddress("glTextureStorageMem3DEXT");
  pfn_glTextureStorageMem3DMultisampleEXT = (PFNGLTEXTURESTORAGEMEM3DMULTISAMPLEEXTPROC)fnGetProcAddress("glTextureStorageMem3DMultisampleEXT");
  pfn_glNamedBufferStorageMemEXT = (PFNGLNAMEDBUFFERSTORAGEMEMEXTPROC)fnGetProcAddress("glNamedBufferStorageMemEXT");
  pfn_glTexStorageMem1DEXT = (PFNGLTEXSTORAGEMEM1DEXTPROC)fnGetProcAddress("glTexStorageMem1DEXT");
  pfn_glTextureStorageMem1DEXT = (PFNGLTEXTURESTORAGEMEM1DEXTPROC)fnGetProcAddress("glTextureStorageMem1DEXT");
  int success = has_extension("GL_EXT_memory_object");
  success = success && (pfn_glGetUnsignedBytevEXT != 0);
  success = success && (pfn_glGetUnsignedBytei_vEXT != 0);
  success = success && (pfn_glDeleteMemoryObjectsEXT != 0);
  success = success && (pfn_glIsMemoryObjectEXT != 0);
  success = success && (pfn_glCreateMemoryObjectsEXT != 0);
  success = success && (pfn_glMemoryObjectParameterivEXT != 0);
  success = success && (pfn_glGetMemoryObjectParameterivEXT != 0);
  success = success && (pfn_glTexStorageMem2DEXT != 0);
  success = success && (pfn_glTexStorageMem2DMultisampleEXT != 0);
  success = success && (pfn_glTexStorageMem3DEXT != 0);
  success = success && (pfn_glTexStorageMem3DMultisampleEXT != 0);
  success = success && (pfn_glBufferStorageMemEXT != 0);
  success = success && (pfn_glTextureStorageMem2DEXT != 0);
  success = success && (pfn_glTextureStorageMem2DMultisampleEXT != 0);
  success = success && (pfn_glTextureStorageMem3DEXT != 0);
  success = success && (pfn_glTextureStorageMem3DMultisampleEXT != 0);
  success = success && (pfn_glNamedBufferStorageMemEXT != 0);
  success = success && (pfn_glTexStorageMem1DEXT != 0);
  success = success && (pfn_glTextureStorageMem1DEXT != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_EXT_memory_object_fd */

static PFNGLIMPORTMEMORYFDEXTPROC pfn_glImportMemoryFdEXT = 0;

GLAPI void APIENTRY glImportMemoryFdEXT(GLuint memory, GLuint64 size, GLenum handleType, GLint fd)
{
  assert(pfn_glImportMemoryFdEXT);
  pfn_glImportMemoryFdEXT(memory,size,handleType,fd);
}

int load_GL_EXT_memory_object_fd(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glImportMemoryFdEXT = (PFNGLIMPORTMEMORYFDEXTPROC)fnGetProcAddress("glImportMemoryFdEXT");
  int success = has_extension("GL_EXT_memory_object_fd");
  success = success && (pfn_glImportMemoryFdEXT != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_EXT_memory_object_win32 */

static PFNGLIMPORTMEMORYWIN32HANDLEEXTPROC pfn_glImportMemoryWin32HandleEXT = 0;
static PFNGLIMPORTMEMORYWIN32NAMEEXTPROC pfn_glImportMemoryWin32NameEXT = 0;

GLAPI void APIENTRY glImportMemoryWin32HandleEXT(GLuint memory, GLuint64 size, GLenum handleType, void* handle)
{
  assert(pfn_glImportMemoryWin32HandleEXT);
  pfn_glImportMemoryWin32HandleEXT(memory,size,handleType,handle);
}
GLAPI void APIENTRY glImportMemoryWin32NameEXT(GLuint memory, GLuint64 size, GLenum handleType, const void* name)
{
  assert(pfn_glImportMemoryWin32NameEXT);
  pfn_glImportMemoryWin32NameEXT(memory,size,handleType,name);
}

int load_GL_EXT_memory_object_win32(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glImportMemoryWin32HandleEXT = (PFNGLIMPORTMEMORYWIN32HANDLEEXTPROC)fnGetProcAddress("glImportMemoryWin32HandleEXT");
  pfn_glImportMemoryWin32NameEXT = (PFNGLIMPORTMEMORYWIN32NAMEEXTPROC)fnGetProcAddress("glImportMemoryWin32NameEXT");
  int success = has_extension("GL_EXT_memory_object_win32");
  success = success && (pfn_glImportMemoryWin32HandleEXT != 0);
  success = success && (pfn_glImportMemoryWin32NameEXT != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_EXT_semaphore */

static PFNGLGENSEMAPHORESEXTPROC pfn_glGenSemaphoresEXT = 0;
static PFNGLDELETESEMAPHORESEXTPROC pfn_glDeleteSemaphoresEXT = 0;
static PFNGLISSEMAPHOREEXTPROC pfn_glIsSemaphoreEXT = 0;
static PFNGLSEMAPHOREPARAMETERUI64VEXTPROC pfn_glSemaphoreParameterui64vEXT = 0;
static PFNGLGETSEMAPHOREPARAMETERUI64VEXTPROC pfn_glGetSemaphoreParameterui64vEXT = 0;
static PFNGLWAITSEMAPHOREEXTPROC pfn_glWaitSemaphoreEXT = 0;
static PFNGLSIGNALSEMAPHOREEXTPROC pfn_glSignalSemaphoreEXT = 0;

GLAPI void APIENTRY glGenSemaphoresEXT(GLsizei n, GLuint* semaphores)
{
  assert(pfn_glGenSemaphoresEXT);
  pfn_glGenSemaphoresEXT(n,semaphores);
}
GLAPI void APIENTRY glDeleteSemaphoresEXT(GLsizei n, const GLuint* semaphores)
{
  assert(pfn_glDeleteSemaphoresEXT);
  pfn_glDeleteSemaphoresEXT(n,semaphores);
}
GLAPI GLboolean APIENTRY glIsSemaphoreEXT(GLuint semaphore)
{
  assert(pfn_glIsSemaphoreEXT);
  return pfn_glIsSemaphoreEXT(semaphore);
}
GLAPI void APIENTRY glSemaphoreParameterui64vEXT(GLuint semaphore, GLenum pname, const GLuint64* params)
{
  assert(pfn_glSemaphoreParameterui64vEXT);
  pfn_glSemaphoreParameterui64vEXT(semaphore,pname,params);
}
GLAPI void APIENTRY glGetSemaphoreParameterui64vEXT(GLuint semaphore, GLenum pname, GLuint64* params)
{
  assert(pfn_glGetSemaphoreParameterui64vEXT);
  pfn_glGetSemaphoreParameterui64vEXT(semaphore,pname,params);
}
GLAPI void APIENTRY glWaitSemaphoreEXT(GLuint semaphore, GLuint numBufferBarriers, const GLuint* buffers, GLuint numTextureBarriers, const GLuint* textures, const GLenum* srcLayouts)
{
  assert(pfn_glWaitSemaphoreEXT);
  pfn_glWaitSemaphoreEXT(semaphore,numBufferBarriers,buffers,numTextureBarriers,textures,srcLayouts);
}
GLAPI void APIENTRY glSignalSemaphoreEXT(GLuint semaphore, GLuint numBufferBarriers, const GLuint* buffers, GLuint numTextureBarriers, const GLuint* textures, const GLenum* dstLayouts)
{
  assert(pfn_glSignalSemaphoreEXT);
  pfn_glSignalSemaphoreEXT(semaphore,numBufferBarriers,buffers,numTextureBarriers,textures,dstLayouts);
}

int load_GL_EXT_semaphore(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glGenSemaphoresEXT = (PFNGLGENSEMAPHORESEXTPROC)fnGetProcAddress("glGenSemaphoresEXT");
  pfn_glDeleteSemaphoresEXT = (PFNGLDELETESEMAPHORESEXTPROC)fnGetProcAddress("glDeleteSemaphoresEXT");
  pfn_glIsSemaphoreEXT = (PFNGLISSEMAPHOREEXTPROC)fnGetProcAddress("glIsSemaphoreEXT");
  pfn_glSemaphoreParameterui64vEXT = (PFNGLSEMAPHOREPARAMETERUI64VEXTPROC)fnGetProcAddress("glSemaphoreParameterui64vEXT");
  pfn_glGetSemaphoreParameterui64vEXT = (PFNGLGETSEMAPHOREPARAMETERUI64VEXTPROC)fnGetProcAddress("glGetSemaphoreParameterui64vEXT");
  pfn_glWaitSemaphoreEXT = (PFNGLWAITSEMAPHOREEXTPROC)fnGetProcAddress("glWaitSemaphoreEXT");
  pfn_glSignalSemaphoreEXT = (PFNGLSIGNALSEMAPHOREEXTPROC)fnGetProcAddress("glSignalSemaphoreEXT");
  int success = has_extension("GL_EXT_semaphore");
  success = success && (pfn_glGenSemaphoresEXT != 0);
  success = success && (pfn_glDeleteSemaphoresEXT != 0);
  success = success && (pfn_glIsSemaphoreEXT != 0);
  success = success && (pfn_glSemaphoreParameterui64vEXT != 0);
  success = success && (pfn_glGetSemaphoreParameterui64vEXT != 0);
  success = success && (pfn_glWaitSemaphoreEXT != 0);
  success = success && (pfn_glSignalSemaphoreEXT != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_EXT_semaphore_fd */

static PFNGLIMPORTSEMAPHOREFDEXTPROC pfn_glImportSemaphoreFdEXT = 0;

GLAPI void APIENTRY glImportSemaphoreFdEXT(GLuint semaphore, GLenum handleType, GLint fd)
{
  assert(pfn_glImportSemaphoreFdEXT);
  pfn_glImportSemaphoreFdEXT(semaphore,handleType,fd);
}

int load_GL_EXT_semaphore_fd(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glImportSemaphoreFdEXT = (PFNGLIMPORTSEMAPHOREFDEXTPROC)fnGetProcAddress("glImportSemaphoreFdEXT");
  int success = has_extension("GL_EXT_semaphore_fd");
  success = success && (pfn_glImportSemaphoreFdEXT != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_EXT_semaphore_win32 */

static PFNGLIMPORTSEMAPHOREWIN32HANDLEEXTPROC pfn_glImportSemaphoreWin32HandleEXT = 0;
static PFNGLIMPORTSEMAPHOREWIN32NAMEEXTPROC pfn_glImportSemaphoreWin32NameEXT = 0;

GLAPI void APIENTRY glImportSemaphoreWin32HandleEXT(GLuint semaphore, GLenum handleType, void* handle)
{
  assert(pfn_glImportSemaphoreWin32HandleEXT);
  pfn_glImportSemaphoreWin32HandleEXT(semaphore,handleType,handle);
}
GLAPI void APIENTRY glImportSemaphoreWin32NameEXT(GLuint semaphore, GLenum handleType, const void* name)
{
  assert(pfn_glImportSemaphoreWin32NameEXT);
  pfn_glImportSemaphoreWin32NameEXT(semaphore,handleType,name);
}

int load_GL_EXT_semaphore_win32(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glImportSemaphoreWin32HandleEXT = (PFNGLIMPORTSEMAPHOREWIN32HANDLEEXTPROC)fnGetProcAddress("glImportSemaphoreWin32HandleEXT");
  pfn_glImportSemaphoreWin32NameEXT = (PFNGLIMPORTSEMAPHOREWIN32NAMEEXTPROC)fnGetProcAddress("glImportSemaphoreWin32NameEXT");
  int success = has_extension("GL_EXT_semaphore_win32");
  success = success && (pfn_glImportSemaphoreWin32HandleEXT != 0);
  success = success && (pfn_glImportSemaphoreWin32NameEXT != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_EXT_texture_compression_latc */



int load_GL_EXT_texture_compression_latc(nvGLLoaderGetProcFN fnGetProcAddress)
{
  int success = has_extension("GL_EXT_texture_compression_latc");
  return success;
}

/* /////////////////////////////////// */
/* GL_EXT_texture_compression_s3tc */



int load_GL_EXT_texture_compression_s3tc(nvGLLoaderGetProcFN fnGetProcAddress)
{
  int success = has_extension("GL_EXT_texture_compression_s3tc");
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_bindless_texture */

static PFNGLGETTEXTUREHANDLENVPROC pfn_glGetTextureHandleNV = 0;
static PFNGLGETTEXTURESAMPLERHANDLENVPROC pfn_glGetTextureSamplerHandleNV = 0;
static PFNGLMAKETEXTUREHANDLERESIDENTNVPROC pfn_glMakeTextureHandleResidentNV = 0;
static PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC pfn_glMakeTextureHandleNonResidentNV = 0;
static PFNGLGETIMAGEHANDLENVPROC pfn_glGetImageHandleNV = 0;
static PFNGLMAKEIMAGEHANDLERESIDENTNVPROC pfn_glMakeImageHandleResidentNV = 0;
static PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC pfn_glMakeImageHandleNonResidentNV = 0;
static PFNGLUNIFORMHANDLEUI64NVPROC pfn_glUniformHandleui64NV = 0;
static PFNGLUNIFORMHANDLEUI64VNVPROC pfn_glUniformHandleui64vNV = 0;
static PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC pfn_glProgramUniformHandleui64NV = 0;
static PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC pfn_glProgramUniformHandleui64vNV = 0;
static PFNGLISTEXTUREHANDLERESIDENTNVPROC pfn_glIsTextureHandleResidentNV = 0;
static PFNGLISIMAGEHANDLERESIDENTNVPROC pfn_glIsImageHandleResidentNV = 0;

GLAPI GLuint64 APIENTRY glGetTextureHandleNV(GLuint texture)
{
  assert(pfn_glGetTextureHandleNV);
  return pfn_glGetTextureHandleNV(texture);
}
GLAPI GLuint64 APIENTRY glGetTextureSamplerHandleNV(GLuint texture, GLuint sampler)
{
  assert(pfn_glGetTextureSamplerHandleNV);
  return pfn_glGetTextureSamplerHandleNV(texture,sampler);
}
GLAPI void APIENTRY glMakeTextureHandleResidentNV(GLuint64 handle)
{
  assert(pfn_glMakeTextureHandleResidentNV);
  pfn_glMakeTextureHandleResidentNV(handle);
}
GLAPI void APIENTRY glMakeTextureHandleNonResidentNV(GLuint64 handle)
{
  assert(pfn_glMakeTextureHandleNonResidentNV);
  pfn_glMakeTextureHandleNonResidentNV(handle);
}
GLAPI GLuint64 APIENTRY glGetImageHandleNV(GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format)
{
  assert(pfn_glGetImageHandleNV);
  return pfn_glGetImageHandleNV(texture,level,layered,layer,format);
}
GLAPI void APIENTRY glMakeImageHandleResidentNV(GLuint64 handle, GLenum access)
{
  assert(pfn_glMakeImageHandleResidentNV);
  pfn_glMakeImageHandleResidentNV(handle,access);
}
GLAPI void APIENTRY glMakeImageHandleNonResidentNV(GLuint64 handle)
{
  assert(pfn_glMakeImageHandleNonResidentNV);
  pfn_glMakeImageHandleNonResidentNV(handle);
}
GLAPI void APIENTRY glUniformHandleui64NV(GLint location, GLuint64 value)
{
  assert(pfn_glUniformHandleui64NV);
  pfn_glUniformHandleui64NV(location,value);
}
GLAPI void APIENTRY glUniformHandleui64vNV(GLint location, GLsizei count, const GLuint64* value)
{
  assert(pfn_glUniformHandleui64vNV);
  pfn_glUniformHandleui64vNV(location,count,value);
}
GLAPI void APIENTRY glProgramUniformHandleui64NV(GLuint program, GLint location, GLuint64 value)
{
  assert(pfn_glProgramUniformHandleui64NV);
  pfn_glProgramUniformHandleui64NV(program,location,value);
}
GLAPI void APIENTRY glProgramUniformHandleui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64* values)
{
  assert(pfn_glProgramUniformHandleui64vNV);
  pfn_glProgramUniformHandleui64vNV(program,location,count,values);
}
GLAPI GLboolean APIENTRY glIsTextureHandleResidentNV(GLuint64 handle)
{
  assert(pfn_glIsTextureHandleResidentNV);
  return pfn_glIsTextureHandleResidentNV(handle);
}
GLAPI GLboolean APIENTRY glIsImageHandleResidentNV(GLuint64 handle)
{
  assert(pfn_glIsImageHandleResidentNV);
  return pfn_glIsImageHandleResidentNV(handle);
}

int load_GL_NV_bindless_texture(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glGetTextureHandleNV = (PFNGLGETTEXTUREHANDLENVPROC)fnGetProcAddress("glGetTextureHandleNV");
  pfn_glGetTextureSamplerHandleNV = (PFNGLGETTEXTURESAMPLERHANDLENVPROC)fnGetProcAddress("glGetTextureSamplerHandleNV");
  pfn_glMakeTextureHandleResidentNV = (PFNGLMAKETEXTUREHANDLERESIDENTNVPROC)fnGetProcAddress("glMakeTextureHandleResidentNV");
  pfn_glMakeTextureHandleNonResidentNV = (PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC)fnGetProcAddress("glMakeTextureHandleNonResidentNV");
  pfn_glGetImageHandleNV = (PFNGLGETIMAGEHANDLENVPROC)fnGetProcAddress("glGetImageHandleNV");
  pfn_glMakeImageHandleResidentNV = (PFNGLMAKEIMAGEHANDLERESIDENTNVPROC)fnGetProcAddress("glMakeImageHandleResidentNV");
  pfn_glMakeImageHandleNonResidentNV = (PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC)fnGetProcAddress("glMakeImageHandleNonResidentNV");
  pfn_glUniformHandleui64NV = (PFNGLUNIFORMHANDLEUI64NVPROC)fnGetProcAddress("glUniformHandleui64NV");
  pfn_glUniformHandleui64vNV = (PFNGLUNIFORMHANDLEUI64VNVPROC)fnGetProcAddress("glUniformHandleui64vNV");
  pfn_glProgramUniformHandleui64NV = (PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC)fnGetProcAddress("glProgramUniformHandleui64NV");
  pfn_glProgramUniformHandleui64vNV = (PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC)fnGetProcAddress("glProgramUniformHandleui64vNV");
  pfn_glIsTextureHandleResidentNV = (PFNGLISTEXTUREHANDLERESIDENTNVPROC)fnGetProcAddress("glIsTextureHandleResidentNV");
  pfn_glIsImageHandleResidentNV = (PFNGLISIMAGEHANDLERESIDENTNVPROC)fnGetProcAddress("glIsImageHandleResidentNV");
  int success = has_extension("GL_NV_bindless_texture");
  success = success && (pfn_glGetTextureHandleNV != 0);
  success = success && (pfn_glGetTextureSamplerHandleNV != 0);
  success = success && (pfn_glMakeTextureHandleResidentNV != 0);
  success = success && (pfn_glMakeTextureHandleNonResidentNV != 0);
  success = success && (pfn_glGetImageHandleNV != 0);
  success = success && (pfn_glMakeImageHandleResidentNV != 0);
  success = success && (pfn_glMakeImageHandleNonResidentNV != 0);
  success = success && (pfn_glUniformHandleui64NV != 0);
  success = success && (pfn_glUniformHandleui64vNV != 0);
  success = success && (pfn_glProgramUniformHandleui64NV != 0);
  success = success && (pfn_glProgramUniformHandleui64vNV != 0);
  success = success && (pfn_glIsTextureHandleResidentNV != 0);
  success = success && (pfn_glIsImageHandleResidentNV != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_blend_equation_advanced */

static PFNGLBLENDPARAMETERINVPROC pfn_glBlendParameteriNV = 0;
static PFNGLBLENDBARRIERNVPROC pfn_glBlendBarrierNV = 0;

GLAPI void APIENTRY glBlendParameteriNV(GLenum pname, GLint value)
{
  assert(pfn_glBlendParameteriNV);
  pfn_glBlendParameteriNV(pname,value);
}
GLAPI void APIENTRY glBlendBarrierNV(void)
{
  assert(pfn_glBlendBarrierNV);
  pfn_glBlendBarrierNV();
}

int load_GL_NV_blend_equation_advanced(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glBlendParameteriNV = (PFNGLBLENDPARAMETERINVPROC)fnGetProcAddress("glBlendParameteriNV");
  pfn_glBlendBarrierNV = (PFNGLBLENDBARRIERNVPROC)fnGetProcAddress("glBlendBarrierNV");
  int success = has_extension("GL_NV_blend_equation_advanced");
  success = success && (pfn_glBlendParameteriNV != 0);
  success = success && (pfn_glBlendBarrierNV != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_clip_space_w_scaling */

static PFNGLVIEWPORTPOSITIONWSCALENVPROC pfn_glViewportPositionWScaleNV = 0;

GLAPI void APIENTRY glViewportPositionWScaleNV(GLuint index, GLfloat xcoeff, GLfloat ycoeff)
{
  assert(pfn_glViewportPositionWScaleNV);
  pfn_glViewportPositionWScaleNV(index,xcoeff,ycoeff);
}

int load_GL_NV_clip_space_w_scaling(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glViewportPositionWScaleNV = (PFNGLVIEWPORTPOSITIONWSCALENVPROC)fnGetProcAddress("glViewportPositionWScaleNV");
  int success = has_extension("GL_NV_clip_space_w_scaling");
  success = success && (pfn_glViewportPositionWScaleNV != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_command_list */

static PFNGLCREATESTATESNVPROC pfn_glCreateStatesNV = 0;
static PFNGLDELETESTATESNVPROC pfn_glDeleteStatesNV = 0;
static PFNGLISSTATENVPROC pfn_glIsStateNV = 0;
static PFNGLSTATECAPTURENVPROC pfn_glStateCaptureNV = 0;
static PFNGLGETCOMMANDHEADERNVPROC pfn_glGetCommandHeaderNV = 0;
static PFNGLGETSTAGEINDEXNVPROC pfn_glGetStageIndexNV = 0;
static PFNGLDRAWCOMMANDSNVPROC pfn_glDrawCommandsNV = 0;
static PFNGLDRAWCOMMANDSADDRESSNVPROC pfn_glDrawCommandsAddressNV = 0;
static PFNGLDRAWCOMMANDSSTATESNVPROC pfn_glDrawCommandsStatesNV = 0;
static PFNGLDRAWCOMMANDSSTATESADDRESSNVPROC pfn_glDrawCommandsStatesAddressNV = 0;
static PFNGLCREATECOMMANDLISTSNVPROC pfn_glCreateCommandListsNV = 0;
static PFNGLDELETECOMMANDLISTSNVPROC pfn_glDeleteCommandListsNV = 0;
static PFNGLISCOMMANDLISTNVPROC pfn_glIsCommandListNV = 0;
static PFNGLLISTDRAWCOMMANDSSTATESCLIENTNVPROC pfn_glListDrawCommandsStatesClientNV = 0;
static PFNGLCOMMANDLISTSEGMENTSNVPROC pfn_glCommandListSegmentsNV = 0;
static PFNGLCOMPILECOMMANDLISTNVPROC pfn_glCompileCommandListNV = 0;
static PFNGLCALLCOMMANDLISTNVPROC pfn_glCallCommandListNV = 0;

GLAPI void APIENTRY glCreateStatesNV(GLsizei n, GLuint* states)
{
  assert(pfn_glCreateStatesNV);
  pfn_glCreateStatesNV(n,states);
}
GLAPI void APIENTRY glDeleteStatesNV(GLsizei n, const GLuint* states)
{
  assert(pfn_glDeleteStatesNV);
  pfn_glDeleteStatesNV(n,states);
}
GLAPI GLboolean APIENTRY glIsStateNV(GLuint state)
{
  assert(pfn_glIsStateNV);
  return pfn_glIsStateNV(state);
}
GLAPI void APIENTRY glStateCaptureNV(GLuint state, GLenum mode)
{
  assert(pfn_glStateCaptureNV);
  pfn_glStateCaptureNV(state,mode);
}
GLAPI GLuint APIENTRY glGetCommandHeaderNV(GLenum tokenID, GLuint size)
{
  assert(pfn_glGetCommandHeaderNV);
  return pfn_glGetCommandHeaderNV(tokenID,size);
}
GLAPI GLushort APIENTRY glGetStageIndexNV(GLenum shadertype)
{
  assert(pfn_glGetStageIndexNV);
  return pfn_glGetStageIndexNV(shadertype);
}
GLAPI void APIENTRY glDrawCommandsNV(GLenum primitiveMode, GLuint buffer, const GLintptr* indirects, const GLsizei* sizes, GLuint count)
{
  assert(pfn_glDrawCommandsNV);
  pfn_glDrawCommandsNV(primitiveMode,buffer,indirects,sizes,count);
}
GLAPI void APIENTRY glDrawCommandsAddressNV(GLenum primitiveMode, const GLuint64* indirects, const GLsizei* sizes, GLuint count)
{
  assert(pfn_glDrawCommandsAddressNV);
  pfn_glDrawCommandsAddressNV(primitiveMode,indirects,sizes,count);
}
GLAPI void APIENTRY glDrawCommandsStatesNV(GLuint buffer, const GLintptr* indirects, const GLsizei* sizes, const GLuint* states, const GLuint* fbos, GLuint count)
{
  assert(pfn_glDrawCommandsStatesNV);
  pfn_glDrawCommandsStatesNV(buffer,indirects,sizes,states,fbos,count);
}
GLAPI void APIENTRY glDrawCommandsStatesAddressNV(const GLuint64* indirects, const GLsizei* sizes, const GLuint* states, const GLuint* fbos, GLuint count)
{
  assert(pfn_glDrawCommandsStatesAddressNV);
  pfn_glDrawCommandsStatesAddressNV(indirects,sizes,states,fbos,count);
}
GLAPI void APIENTRY glCreateCommandListsNV(GLsizei n, GLuint* lists)
{
  assert(pfn_glCreateCommandListsNV);
  pfn_glCreateCommandListsNV(n,lists);
}
GLAPI void APIENTRY glDeleteCommandListsNV(GLsizei n, const GLuint* lists)
{
  assert(pfn_glDeleteCommandListsNV);
  pfn_glDeleteCommandListsNV(n,lists);
}
GLAPI GLboolean APIENTRY glIsCommandListNV(GLuint list)
{
  assert(pfn_glIsCommandListNV);
  return pfn_glIsCommandListNV(list);
}
GLAPI void APIENTRY glListDrawCommandsStatesClientNV(GLuint list, GLuint segment, const void* * indirects, const GLsizei* sizes, const GLuint* states, const GLuint* fbos, GLuint count)
{
  assert(pfn_glListDrawCommandsStatesClientNV);
  pfn_glListDrawCommandsStatesClientNV(list,segment,indirects,sizes,states,fbos,count);
}
GLAPI void APIENTRY glCommandListSegmentsNV(GLuint list, GLuint segments)
{
  assert(pfn_glCommandListSegmentsNV);
  pfn_glCommandListSegmentsNV(list,segments);
}
GLAPI void APIENTRY glCompileCommandListNV(GLuint list)
{
  assert(pfn_glCompileCommandListNV);
  pfn_glCompileCommandListNV(list);
}
GLAPI void APIENTRY glCallCommandListNV(GLuint list)
{
  assert(pfn_glCallCommandListNV);
  pfn_glCallCommandListNV(list);
}

int load_GL_NV_command_list(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glCreateStatesNV = (PFNGLCREATESTATESNVPROC)fnGetProcAddress("glCreateStatesNV");
  pfn_glDeleteStatesNV = (PFNGLDELETESTATESNVPROC)fnGetProcAddress("glDeleteStatesNV");
  pfn_glIsStateNV = (PFNGLISSTATENVPROC)fnGetProcAddress("glIsStateNV");
  pfn_glStateCaptureNV = (PFNGLSTATECAPTURENVPROC)fnGetProcAddress("glStateCaptureNV");
  pfn_glGetCommandHeaderNV = (PFNGLGETCOMMANDHEADERNVPROC)fnGetProcAddress("glGetCommandHeaderNV");
  pfn_glGetStageIndexNV = (PFNGLGETSTAGEINDEXNVPROC)fnGetProcAddress("glGetStageIndexNV");
  pfn_glDrawCommandsNV = (PFNGLDRAWCOMMANDSNVPROC)fnGetProcAddress("glDrawCommandsNV");
  pfn_glDrawCommandsAddressNV = (PFNGLDRAWCOMMANDSADDRESSNVPROC)fnGetProcAddress("glDrawCommandsAddressNV");
  pfn_glDrawCommandsStatesNV = (PFNGLDRAWCOMMANDSSTATESNVPROC)fnGetProcAddress("glDrawCommandsStatesNV");
  pfn_glDrawCommandsStatesAddressNV = (PFNGLDRAWCOMMANDSSTATESADDRESSNVPROC)fnGetProcAddress("glDrawCommandsStatesAddressNV");
  pfn_glCreateCommandListsNV = (PFNGLCREATECOMMANDLISTSNVPROC)fnGetProcAddress("glCreateCommandListsNV");
  pfn_glDeleteCommandListsNV = (PFNGLDELETECOMMANDLISTSNVPROC)fnGetProcAddress("glDeleteCommandListsNV");
  pfn_glIsCommandListNV = (PFNGLISCOMMANDLISTNVPROC)fnGetProcAddress("glIsCommandListNV");
  pfn_glListDrawCommandsStatesClientNV = (PFNGLLISTDRAWCOMMANDSSTATESCLIENTNVPROC)fnGetProcAddress("glListDrawCommandsStatesClientNV");
  pfn_glCommandListSegmentsNV = (PFNGLCOMMANDLISTSEGMENTSNVPROC)fnGetProcAddress("glCommandListSegmentsNV");
  pfn_glCompileCommandListNV = (PFNGLCOMPILECOMMANDLISTNVPROC)fnGetProcAddress("glCompileCommandListNV");
  pfn_glCallCommandListNV = (PFNGLCALLCOMMANDLISTNVPROC)fnGetProcAddress("glCallCommandListNV");
  int success = has_extension("GL_NV_command_list");
  success = success && (pfn_glCreateStatesNV != 0);
  success = success && (pfn_glDeleteStatesNV != 0);
  success = success && (pfn_glIsStateNV != 0);
  success = success && (pfn_glStateCaptureNV != 0);
  success = success && (pfn_glGetCommandHeaderNV != 0);
  success = success && (pfn_glGetStageIndexNV != 0);
  success = success && (pfn_glDrawCommandsNV != 0);
  success = success && (pfn_glDrawCommandsAddressNV != 0);
  success = success && (pfn_glDrawCommandsStatesNV != 0);
  success = success && (pfn_glDrawCommandsStatesAddressNV != 0);
  success = success && (pfn_glCreateCommandListsNV != 0);
  success = success && (pfn_glDeleteCommandListsNV != 0);
  success = success && (pfn_glIsCommandListNV != 0);
  success = success && (pfn_glListDrawCommandsStatesClientNV != 0);
  success = success && (pfn_glCommandListSegmentsNV != 0);
  success = success && (pfn_glCompileCommandListNV != 0);
  success = success && (pfn_glCallCommandListNV != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_compute_shader_derivatives */



int load_GL_NV_compute_shader_derivatives(nvGLLoaderGetProcFN fnGetProcAddress)
{
  int success = has_extension("GL_NV_compute_shader_derivatives");
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_conservative_raster */

static PFNGLSUBPIXELPRECISIONBIASNVPROC pfn_glSubpixelPrecisionBiasNV = 0;

GLAPI void APIENTRY glSubpixelPrecisionBiasNV(GLuint xbits, GLuint ybits)
{
  assert(pfn_glSubpixelPrecisionBiasNV);
  pfn_glSubpixelPrecisionBiasNV(xbits,ybits);
}

int load_GL_NV_conservative_raster(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glSubpixelPrecisionBiasNV = (PFNGLSUBPIXELPRECISIONBIASNVPROC)fnGetProcAddress("glSubpixelPrecisionBiasNV");
  int success = has_extension("GL_NV_conservative_raster");
  success = success && (pfn_glSubpixelPrecisionBiasNV != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_conservative_raster_dilate */

static PFNGLCONSERVATIVERASTERPARAMETERFNVPROC pfn_glConservativeRasterParameterfNV = 0;

GLAPI void APIENTRY glConservativeRasterParameterfNV(GLenum pname, GLfloat value)
{
  assert(pfn_glConservativeRasterParameterfNV);
  pfn_glConservativeRasterParameterfNV(pname,value);
}

int load_GL_NV_conservative_raster_dilate(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glConservativeRasterParameterfNV = (PFNGLCONSERVATIVERASTERPARAMETERFNVPROC)fnGetProcAddress("glConservativeRasterParameterfNV");
  int success = has_extension("GL_NV_conservative_raster_dilate");
  success = success && (pfn_glConservativeRasterParameterfNV != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_conservative_raster_pre_snap */



int load_GL_NV_conservative_raster_pre_snap(nvGLLoaderGetProcFN fnGetProcAddress)
{
  int success = has_extension("GL_NV_conservative_raster_pre_snap");
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_conservative_raster_pre_snap_triangles */

static PFNGLCONSERVATIVERASTERPARAMETERINVPROC pfn_glConservativeRasterParameteriNV = 0;

GLAPI void APIENTRY glConservativeRasterParameteriNV(GLenum pname, GLint param)
{
  assert(pfn_glConservativeRasterParameteriNV);
  pfn_glConservativeRasterParameteriNV(pname,param);
}

int load_GL_NV_conservative_raster_pre_snap_triangles(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glConservativeRasterParameteriNV = (PFNGLCONSERVATIVERASTERPARAMETERINVPROC)fnGetProcAddress("glConservativeRasterParameteriNV");
  int success = has_extension("GL_NV_conservative_raster_pre_snap_triangles");
  success = success && (pfn_glConservativeRasterParameteriNV != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_conservative_raster_underestimation */



int load_GL_NV_conservative_raster_underestimation(nvGLLoaderGetProcFN fnGetProcAddress)
{
  int success = has_extension("GL_NV_conservative_raster_underestimation");
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_draw_vulkan_image */

static PFNGLDRAWVKIMAGENVPROC pfn_glDrawVkImageNV = 0;
static PFNGLGETVKPROCADDRNVPROC pfn_glGetVkProcAddrNV = 0;
static PFNGLWAITVKSEMAPHORENVPROC pfn_glWaitVkSemaphoreNV = 0;
static PFNGLSIGNALVKSEMAPHORENVPROC pfn_glSignalVkSemaphoreNV = 0;
static PFNGLSIGNALVKFENCENVPROC pfn_glSignalVkFenceNV = 0;

GLAPI void APIENTRY glDrawVkImageNV(GLuint64 vkImage, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1)
{
  assert(pfn_glDrawVkImageNV);
  pfn_glDrawVkImageNV(vkImage,sampler,x0,y0,x1,y1,z,s0,t0,s1,t1);
}
GLAPI GLVULKANPROCNV APIENTRY glGetVkProcAddrNV(const GLchar* name)
{
  assert(pfn_glGetVkProcAddrNV);
  return pfn_glGetVkProcAddrNV(name);
}
GLAPI void APIENTRY glWaitVkSemaphoreNV(GLuint64 vkSemaphore)
{
  assert(pfn_glWaitVkSemaphoreNV);
  pfn_glWaitVkSemaphoreNV(vkSemaphore);
}
GLAPI void APIENTRY glSignalVkSemaphoreNV(GLuint64 vkSemaphore)
{
  assert(pfn_glSignalVkSemaphoreNV);
  pfn_glSignalVkSemaphoreNV(vkSemaphore);
}
GLAPI void APIENTRY glSignalVkFenceNV(GLuint64 vkFence)
{
  assert(pfn_glSignalVkFenceNV);
  pfn_glSignalVkFenceNV(vkFence);
}

int load_GL_NV_draw_vulkan_image(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glDrawVkImageNV = (PFNGLDRAWVKIMAGENVPROC)fnGetProcAddress("glDrawVkImageNV");
  pfn_glGetVkProcAddrNV = (PFNGLGETVKPROCADDRNVPROC)fnGetProcAddress("glGetVkProcAddrNV");
  pfn_glWaitVkSemaphoreNV = (PFNGLWAITVKSEMAPHORENVPROC)fnGetProcAddress("glWaitVkSemaphoreNV");
  pfn_glSignalVkSemaphoreNV = (PFNGLSIGNALVKSEMAPHORENVPROC)fnGetProcAddress("glSignalVkSemaphoreNV");
  pfn_glSignalVkFenceNV = (PFNGLSIGNALVKFENCENVPROC)fnGetProcAddress("glSignalVkFenceNV");
  int success = has_extension("GL_NV_draw_vulkan_image");
  success = success && (pfn_glDrawVkImageNV != 0);
  success = success && (pfn_glGetVkProcAddrNV != 0);
  success = success && (pfn_glWaitVkSemaphoreNV != 0);
  success = success && (pfn_glSignalVkSemaphoreNV != 0);
  success = success && (pfn_glSignalVkFenceNV != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_fill_rectangle */



int load_GL_NV_fill_rectangle(nvGLLoaderGetProcFN fnGetProcAddress)
{
  int success = has_extension("GL_NV_fill_rectangle");
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_fragment_coverage_to_color */

static PFNGLFRAGMENTCOVERAGECOLORNVPROC pfn_glFragmentCoverageColorNV = 0;

GLAPI void APIENTRY glFragmentCoverageColorNV(GLuint color)
{
  assert(pfn_glFragmentCoverageColorNV);
  pfn_glFragmentCoverageColorNV(color);
}

int load_GL_NV_fragment_coverage_to_color(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glFragmentCoverageColorNV = (PFNGLFRAGMENTCOVERAGECOLORNVPROC)fnGetProcAddress("glFragmentCoverageColorNV");
  int success = has_extension("GL_NV_fragment_coverage_to_color");
  success = success && (pfn_glFragmentCoverageColorNV != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_fragment_shader_barycentric */



int load_GL_NV_fragment_shader_barycentric(nvGLLoaderGetProcFN fnGetProcAddress)
{
  int success = has_extension("GL_NV_fragment_shader_barycentric");
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_fragment_shader_interlock */



int load_GL_NV_fragment_shader_interlock(nvGLLoaderGetProcFN fnGetProcAddress)
{
  int success = has_extension("GL_NV_fragment_shader_interlock");
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_framebuffer_mixed_samples */

static PFNGLCOVERAGEMODULATIONTABLENVPROC pfn_glCoverageModulationTableNV = 0;
static PFNGLGETCOVERAGEMODULATIONTABLENVPROC pfn_glGetCoverageModulationTableNV = 0;
static PFNGLCOVERAGEMODULATIONNVPROC pfn_glCoverageModulationNV = 0;

GLAPI void APIENTRY glCoverageModulationTableNV(GLsizei n, const GLfloat* v)
{
  assert(pfn_glCoverageModulationTableNV);
  pfn_glCoverageModulationTableNV(n,v);
}
GLAPI void APIENTRY glGetCoverageModulationTableNV(GLsizei bufsize, GLfloat* v)
{
  assert(pfn_glGetCoverageModulationTableNV);
  pfn_glGetCoverageModulationTableNV(bufsize,v);
}
GLAPI void APIENTRY glCoverageModulationNV(GLenum components)
{
  assert(pfn_glCoverageModulationNV);
  pfn_glCoverageModulationNV(components);
}

int load_GL_NV_framebuffer_mixed_samples(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glCoverageModulationTableNV = (PFNGLCOVERAGEMODULATIONTABLENVPROC)fnGetProcAddress("glCoverageModulationTableNV");
  pfn_glGetCoverageModulationTableNV = (PFNGLGETCOVERAGEMODULATIONTABLENVPROC)fnGetProcAddress("glGetCoverageModulationTableNV");
  pfn_glCoverageModulationNV = (PFNGLCOVERAGEMODULATIONNVPROC)fnGetProcAddress("glCoverageModulationNV");
  int success = has_extension("GL_NV_framebuffer_mixed_samples");
  success = success && (pfn_glCoverageModulationTableNV != 0);
  success = success && (pfn_glGetCoverageModulationTableNV != 0);
  success = success && (pfn_glCoverageModulationNV != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_gpu_multicast */

static PFNGLRENDERGPUMASKNVPROC pfn_glRenderGpuMaskNV = 0;
static PFNGLMULTICASTBUFFERSUBDATANVPROC pfn_glMulticastBufferSubDataNV = 0;
static PFNGLMULTICASTCOPYBUFFERSUBDATANVPROC pfn_glMulticastCopyBufferSubDataNV = 0;
static PFNGLMULTICASTCOPYIMAGESUBDATANVPROC pfn_glMulticastCopyImageSubDataNV = 0;
static PFNGLMULTICASTBLITFRAMEBUFFERNVPROC pfn_glMulticastBlitFramebufferNV = 0;
static PFNGLMULTICASTFRAMEBUFFERSAMPLELOCATIONSFVNVPROC pfn_glMulticastFramebufferSampleLocationsfvNV = 0;
static PFNGLMULTICASTBARRIERNVPROC pfn_glMulticastBarrierNV = 0;
static PFNGLMULTICASTWAITSYNCNVPROC pfn_glMulticastWaitSyncNV = 0;
static PFNGLMULTICASTGETQUERYOBJECTIVNVPROC pfn_glMulticastGetQueryObjectivNV = 0;
static PFNGLMULTICASTGETQUERYOBJECTUIVNVPROC pfn_glMulticastGetQueryObjectuivNV = 0;
static PFNGLMULTICASTGETQUERYOBJECTI64VNVPROC pfn_glMulticastGetQueryObjecti64vNV = 0;
static PFNGLMULTICASTGETQUERYOBJECTUI64VNVPROC pfn_glMulticastGetQueryObjectui64vNV = 0;

GLAPI void APIENTRY glRenderGpuMaskNV(GLbitfield mask)
{
  assert(pfn_glRenderGpuMaskNV);
  pfn_glRenderGpuMaskNV(mask);
}
GLAPI void APIENTRY glMulticastBufferSubDataNV(GLbitfield gpuMask, GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data)
{
  assert(pfn_glMulticastBufferSubDataNV);
  pfn_glMulticastBufferSubDataNV(gpuMask,buffer,offset,size,data);
}
GLAPI void APIENTRY glMulticastCopyBufferSubDataNV(GLuint readGpu, GLbitfield writeGpuMask, GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
{
  assert(pfn_glMulticastCopyBufferSubDataNV);
  pfn_glMulticastCopyBufferSubDataNV(readGpu,writeGpuMask,readBuffer,writeBuffer,readOffset,writeOffset,size);
}
GLAPI void APIENTRY glMulticastCopyImageSubDataNV(GLuint srcGpu, GLbitfield dstGpuMask, GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth)
{
  assert(pfn_glMulticastCopyImageSubDataNV);
  pfn_glMulticastCopyImageSubDataNV(srcGpu,dstGpuMask,srcName,srcTarget,srcLevel,srcX,srcY,srcZ,dstName,dstTarget,dstLevel,dstX,dstY,dstZ,srcWidth,srcHeight,srcDepth);
}
GLAPI void APIENTRY glMulticastBlitFramebufferNV(GLuint srcGpu, GLuint dstGpu, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
{
  assert(pfn_glMulticastBlitFramebufferNV);
  pfn_glMulticastBlitFramebufferNV(srcGpu,dstGpu,srcX0,srcY0,srcX1,srcY1,dstX0,dstY0,dstX1,dstY1,mask,filter);
}
GLAPI void APIENTRY glMulticastFramebufferSampleLocationsfvNV(GLuint gpu, GLuint framebuffer, GLuint start, GLsizei count, const GLfloat* v)
{
  assert(pfn_glMulticastFramebufferSampleLocationsfvNV);
  pfn_glMulticastFramebufferSampleLocationsfvNV(gpu,framebuffer,start,count,v);
}
GLAPI void APIENTRY glMulticastBarrierNV(void)
{
  assert(pfn_glMulticastBarrierNV);
  pfn_glMulticastBarrierNV();
}
GLAPI void APIENTRY glMulticastWaitSyncNV(GLuint signalGpu, GLbitfield waitGpuMask)
{
  assert(pfn_glMulticastWaitSyncNV);
  pfn_glMulticastWaitSyncNV(signalGpu,waitGpuMask);
}
GLAPI void APIENTRY glMulticastGetQueryObjectivNV(GLuint gpu, GLuint id, GLenum pname, GLint* params)
{
  assert(pfn_glMulticastGetQueryObjectivNV);
  pfn_glMulticastGetQueryObjectivNV(gpu,id,pname,params);
}
GLAPI void APIENTRY glMulticastGetQueryObjectuivNV(GLuint gpu, GLuint id, GLenum pname, GLuint* params)
{
  assert(pfn_glMulticastGetQueryObjectuivNV);
  pfn_glMulticastGetQueryObjectuivNV(gpu,id,pname,params);
}
GLAPI void APIENTRY glMulticastGetQueryObjecti64vNV(GLuint gpu, GLuint id, GLenum pname, GLint64* params)
{
  assert(pfn_glMulticastGetQueryObjecti64vNV);
  pfn_glMulticastGetQueryObjecti64vNV(gpu,id,pname,params);
}
GLAPI void APIENTRY glMulticastGetQueryObjectui64vNV(GLuint gpu, GLuint id, GLenum pname, GLuint64* params)
{
  assert(pfn_glMulticastGetQueryObjectui64vNV);
  pfn_glMulticastGetQueryObjectui64vNV(gpu,id,pname,params);
}

int load_GL_NV_gpu_multicast(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glRenderGpuMaskNV = (PFNGLRENDERGPUMASKNVPROC)fnGetProcAddress("glRenderGpuMaskNV");
  pfn_glMulticastBufferSubDataNV = (PFNGLMULTICASTBUFFERSUBDATANVPROC)fnGetProcAddress("glMulticastBufferSubDataNV");
  pfn_glMulticastCopyBufferSubDataNV = (PFNGLMULTICASTCOPYBUFFERSUBDATANVPROC)fnGetProcAddress("glMulticastCopyBufferSubDataNV");
  pfn_glMulticastCopyImageSubDataNV = (PFNGLMULTICASTCOPYIMAGESUBDATANVPROC)fnGetProcAddress("glMulticastCopyImageSubDataNV");
  pfn_glMulticastBlitFramebufferNV = (PFNGLMULTICASTBLITFRAMEBUFFERNVPROC)fnGetProcAddress("glMulticastBlitFramebufferNV");
  pfn_glMulticastFramebufferSampleLocationsfvNV = (PFNGLMULTICASTFRAMEBUFFERSAMPLELOCATIONSFVNVPROC)fnGetProcAddress("glMulticastFramebufferSampleLocationsfvNV");
  pfn_glMulticastBarrierNV = (PFNGLMULTICASTBARRIERNVPROC)fnGetProcAddress("glMulticastBarrierNV");
  pfn_glMulticastWaitSyncNV = (PFNGLMULTICASTWAITSYNCNVPROC)fnGetProcAddress("glMulticastWaitSyncNV");
  pfn_glMulticastGetQueryObjectivNV = (PFNGLMULTICASTGETQUERYOBJECTIVNVPROC)fnGetProcAddress("glMulticastGetQueryObjectivNV");
  pfn_glMulticastGetQueryObjectuivNV = (PFNGLMULTICASTGETQUERYOBJECTUIVNVPROC)fnGetProcAddress("glMulticastGetQueryObjectuivNV");
  pfn_glMulticastGetQueryObjecti64vNV = (PFNGLMULTICASTGETQUERYOBJECTI64VNVPROC)fnGetProcAddress("glMulticastGetQueryObjecti64vNV");
  pfn_glMulticastGetQueryObjectui64vNV = (PFNGLMULTICASTGETQUERYOBJECTUI64VNVPROC)fnGetProcAddress("glMulticastGetQueryObjectui64vNV");
  int success = has_extension("GL_NV_gpu_multicast");
  success = success && (pfn_glRenderGpuMaskNV != 0);
  success = success && (pfn_glMulticastBufferSubDataNV != 0);
  success = success && (pfn_glMulticastCopyBufferSubDataNV != 0);
  success = success && (pfn_glMulticastCopyImageSubDataNV != 0);
  success = success && (pfn_glMulticastBlitFramebufferNV != 0);
  success = success && (pfn_glMulticastFramebufferSampleLocationsfvNV != 0);
  success = success && (pfn_glMulticastBarrierNV != 0);
  success = success && (pfn_glMulticastWaitSyncNV != 0);
  success = success && (pfn_glMulticastGetQueryObjectivNV != 0);
  success = success && (pfn_glMulticastGetQueryObjectuivNV != 0);
  success = success && (pfn_glMulticastGetQueryObjecti64vNV != 0);
  success = success && (pfn_glMulticastGetQueryObjectui64vNV != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_gpu_shader5 */

static PFNGLUNIFORM1I64NVPROC pfn_glUniform1i64NV = 0;
static PFNGLUNIFORM2I64NVPROC pfn_glUniform2i64NV = 0;
static PFNGLUNIFORM3I64NVPROC pfn_glUniform3i64NV = 0;
static PFNGLUNIFORM4I64NVPROC pfn_glUniform4i64NV = 0;
static PFNGLUNIFORM1I64VNVPROC pfn_glUniform1i64vNV = 0;
static PFNGLUNIFORM2I64VNVPROC pfn_glUniform2i64vNV = 0;
static PFNGLUNIFORM3I64VNVPROC pfn_glUniform3i64vNV = 0;
static PFNGLUNIFORM4I64VNVPROC pfn_glUniform4i64vNV = 0;
static PFNGLUNIFORM1UI64NVPROC pfn_glUniform1ui64NV = 0;
static PFNGLUNIFORM2UI64NVPROC pfn_glUniform2ui64NV = 0;
static PFNGLUNIFORM3UI64NVPROC pfn_glUniform3ui64NV = 0;
static PFNGLUNIFORM4UI64NVPROC pfn_glUniform4ui64NV = 0;
static PFNGLUNIFORM1UI64VNVPROC pfn_glUniform1ui64vNV = 0;
static PFNGLUNIFORM2UI64VNVPROC pfn_glUniform2ui64vNV = 0;
static PFNGLUNIFORM3UI64VNVPROC pfn_glUniform3ui64vNV = 0;
static PFNGLUNIFORM4UI64VNVPROC pfn_glUniform4ui64vNV = 0;
static PFNGLGETUNIFORMI64VNVPROC pfn_glGetUniformi64vNV = 0;
static PFNGLPROGRAMUNIFORM1I64NVPROC pfn_glProgramUniform1i64NV = 0;
static PFNGLPROGRAMUNIFORM2I64NVPROC pfn_glProgramUniform2i64NV = 0;
static PFNGLPROGRAMUNIFORM3I64NVPROC pfn_glProgramUniform3i64NV = 0;
static PFNGLPROGRAMUNIFORM4I64NVPROC pfn_glProgramUniform4i64NV = 0;
static PFNGLPROGRAMUNIFORM1I64VNVPROC pfn_glProgramUniform1i64vNV = 0;
static PFNGLPROGRAMUNIFORM2I64VNVPROC pfn_glProgramUniform2i64vNV = 0;
static PFNGLPROGRAMUNIFORM3I64VNVPROC pfn_glProgramUniform3i64vNV = 0;
static PFNGLPROGRAMUNIFORM4I64VNVPROC pfn_glProgramUniform4i64vNV = 0;
static PFNGLPROGRAMUNIFORM1UI64NVPROC pfn_glProgramUniform1ui64NV = 0;
static PFNGLPROGRAMUNIFORM2UI64NVPROC pfn_glProgramUniform2ui64NV = 0;
static PFNGLPROGRAMUNIFORM3UI64NVPROC pfn_glProgramUniform3ui64NV = 0;
static PFNGLPROGRAMUNIFORM4UI64NVPROC pfn_glProgramUniform4ui64NV = 0;
static PFNGLPROGRAMUNIFORM1UI64VNVPROC pfn_glProgramUniform1ui64vNV = 0;
static PFNGLPROGRAMUNIFORM2UI64VNVPROC pfn_glProgramUniform2ui64vNV = 0;
static PFNGLPROGRAMUNIFORM3UI64VNVPROC pfn_glProgramUniform3ui64vNV = 0;
static PFNGLPROGRAMUNIFORM4UI64VNVPROC pfn_glProgramUniform4ui64vNV = 0;

GLAPI void APIENTRY glUniform1i64NV(GLint location, GLint64EXT x)
{
  assert(pfn_glUniform1i64NV);
  pfn_glUniform1i64NV(location,x);
}
GLAPI void APIENTRY glUniform2i64NV(GLint location, GLint64EXT x, GLint64EXT y)
{
  assert(pfn_glUniform2i64NV);
  pfn_glUniform2i64NV(location,x,y);
}
GLAPI void APIENTRY glUniform3i64NV(GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z)
{
  assert(pfn_glUniform3i64NV);
  pfn_glUniform3i64NV(location,x,y,z);
}
GLAPI void APIENTRY glUniform4i64NV(GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w)
{
  assert(pfn_glUniform4i64NV);
  pfn_glUniform4i64NV(location,x,y,z,w);
}
GLAPI void APIENTRY glUniform1i64vNV(GLint location, GLsizei count, const GLint64EXT* value)
{
  assert(pfn_glUniform1i64vNV);
  pfn_glUniform1i64vNV(location,count,value);
}
GLAPI void APIENTRY glUniform2i64vNV(GLint location, GLsizei count, const GLint64EXT* value)
{
  assert(pfn_glUniform2i64vNV);
  pfn_glUniform2i64vNV(location,count,value);
}
GLAPI void APIENTRY glUniform3i64vNV(GLint location, GLsizei count, const GLint64EXT* value)
{
  assert(pfn_glUniform3i64vNV);
  pfn_glUniform3i64vNV(location,count,value);
}
GLAPI void APIENTRY glUniform4i64vNV(GLint location, GLsizei count, const GLint64EXT* value)
{
  assert(pfn_glUniform4i64vNV);
  pfn_glUniform4i64vNV(location,count,value);
}
GLAPI void APIENTRY glUniform1ui64NV(GLint location, GLuint64EXT x)
{
  assert(pfn_glUniform1ui64NV);
  pfn_glUniform1ui64NV(location,x);
}
GLAPI void APIENTRY glUniform2ui64NV(GLint location, GLuint64EXT x, GLuint64EXT y)
{
  assert(pfn_glUniform2ui64NV);
  pfn_glUniform2ui64NV(location,x,y);
}
GLAPI void APIENTRY glUniform3ui64NV(GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z)
{
  assert(pfn_glUniform3ui64NV);
  pfn_glUniform3ui64NV(location,x,y,z);
}
GLAPI void APIENTRY glUniform4ui64NV(GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w)
{
  assert(pfn_glUniform4ui64NV);
  pfn_glUniform4ui64NV(location,x,y,z,w);
}
GLAPI void APIENTRY glUniform1ui64vNV(GLint location, GLsizei count, const GLuint64EXT* value)
{
  assert(pfn_glUniform1ui64vNV);
  pfn_glUniform1ui64vNV(location,count,value);
}
GLAPI void APIENTRY glUniform2ui64vNV(GLint location, GLsizei count, const GLuint64EXT* value)
{
  assert(pfn_glUniform2ui64vNV);
  pfn_glUniform2ui64vNV(location,count,value);
}
GLAPI void APIENTRY glUniform3ui64vNV(GLint location, GLsizei count, const GLuint64EXT* value)
{
  assert(pfn_glUniform3ui64vNV);
  pfn_glUniform3ui64vNV(location,count,value);
}
GLAPI void APIENTRY glUniform4ui64vNV(GLint location, GLsizei count, const GLuint64EXT* value)
{
  assert(pfn_glUniform4ui64vNV);
  pfn_glUniform4ui64vNV(location,count,value);
}
GLAPI void APIENTRY glGetUniformi64vNV(GLuint program, GLint location, GLint64EXT* params)
{
  assert(pfn_glGetUniformi64vNV);
  pfn_glGetUniformi64vNV(program,location,params);
}
GLAPI void APIENTRY glProgramUniform1i64NV(GLuint program, GLint location, GLint64EXT x)
{
  assert(pfn_glProgramUniform1i64NV);
  pfn_glProgramUniform1i64NV(program,location,x);
}
GLAPI void APIENTRY glProgramUniform2i64NV(GLuint program, GLint location, GLint64EXT x, GLint64EXT y)
{
  assert(pfn_glProgramUniform2i64NV);
  pfn_glProgramUniform2i64NV(program,location,x,y);
}
GLAPI void APIENTRY glProgramUniform3i64NV(GLuint program, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z)
{
  assert(pfn_glProgramUniform3i64NV);
  pfn_glProgramUniform3i64NV(program,location,x,y,z);
}
GLAPI void APIENTRY glProgramUniform4i64NV(GLuint program, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w)
{
  assert(pfn_glProgramUniform4i64NV);
  pfn_glProgramUniform4i64NV(program,location,x,y,z,w);
}
GLAPI void APIENTRY glProgramUniform1i64vNV(GLuint program, GLint location, GLsizei count, const GLint64EXT* value)
{
  assert(pfn_glProgramUniform1i64vNV);
  pfn_glProgramUniform1i64vNV(program,location,count,value);
}
GLAPI void APIENTRY glProgramUniform2i64vNV(GLuint program, GLint location, GLsizei count, const GLint64EXT* value)
{
  assert(pfn_glProgramUniform2i64vNV);
  pfn_glProgramUniform2i64vNV(program,location,count,value);
}
GLAPI void APIENTRY glProgramUniform3i64vNV(GLuint program, GLint location, GLsizei count, const GLint64EXT* value)
{
  assert(pfn_glProgramUniform3i64vNV);
  pfn_glProgramUniform3i64vNV(program,location,count,value);
}
GLAPI void APIENTRY glProgramUniform4i64vNV(GLuint program, GLint location, GLsizei count, const GLint64EXT* value)
{
  assert(pfn_glProgramUniform4i64vNV);
  pfn_glProgramUniform4i64vNV(program,location,count,value);
}
GLAPI void APIENTRY glProgramUniform1ui64NV(GLuint program, GLint location, GLuint64EXT x)
{
  assert(pfn_glProgramUniform1ui64NV);
  pfn_glProgramUniform1ui64NV(program,location,x);
}
GLAPI void APIENTRY glProgramUniform2ui64NV(GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y)
{
  assert(pfn_glProgramUniform2ui64NV);
  pfn_glProgramUniform2ui64NV(program,location,x,y);
}
GLAPI void APIENTRY glProgramUniform3ui64NV(GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z)
{
  assert(pfn_glProgramUniform3ui64NV);
  pfn_glProgramUniform3ui64NV(program,location,x,y,z);
}
GLAPI void APIENTRY glProgramUniform4ui64NV(GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w)
{
  assert(pfn_glProgramUniform4ui64NV);
  pfn_glProgramUniform4ui64NV(program,location,x,y,z,w);
}
GLAPI void APIENTRY glProgramUniform1ui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64EXT* value)
{
  assert(pfn_glProgramUniform1ui64vNV);
  pfn_glProgramUniform1ui64vNV(program,location,count,value);
}
GLAPI void APIENTRY glProgramUniform2ui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64EXT* value)
{
  assert(pfn_glProgramUniform2ui64vNV);
  pfn_glProgramUniform2ui64vNV(program,location,count,value);
}
GLAPI void APIENTRY glProgramUniform3ui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64EXT* value)
{
  assert(pfn_glProgramUniform3ui64vNV);
  pfn_glProgramUniform3ui64vNV(program,location,count,value);
}
GLAPI void APIENTRY glProgramUniform4ui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64EXT* value)
{
  assert(pfn_glProgramUniform4ui64vNV);
  pfn_glProgramUniform4ui64vNV(program,location,count,value);
}

int load_GL_NV_gpu_shader5(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glUniform1i64NV = (PFNGLUNIFORM1I64NVPROC)fnGetProcAddress("glUniform1i64NV");
  pfn_glUniform2i64NV = (PFNGLUNIFORM2I64NVPROC)fnGetProcAddress("glUniform2i64NV");
  pfn_glUniform3i64NV = (PFNGLUNIFORM3I64NVPROC)fnGetProcAddress("glUniform3i64NV");
  pfn_glUniform4i64NV = (PFNGLUNIFORM4I64NVPROC)fnGetProcAddress("glUniform4i64NV");
  pfn_glUniform1i64vNV = (PFNGLUNIFORM1I64VNVPROC)fnGetProcAddress("glUniform1i64vNV");
  pfn_glUniform2i64vNV = (PFNGLUNIFORM2I64VNVPROC)fnGetProcAddress("glUniform2i64vNV");
  pfn_glUniform3i64vNV = (PFNGLUNIFORM3I64VNVPROC)fnGetProcAddress("glUniform3i64vNV");
  pfn_glUniform4i64vNV = (PFNGLUNIFORM4I64VNVPROC)fnGetProcAddress("glUniform4i64vNV");
  pfn_glUniform1ui64NV = (PFNGLUNIFORM1UI64NVPROC)fnGetProcAddress("glUniform1ui64NV");
  pfn_glUniform2ui64NV = (PFNGLUNIFORM2UI64NVPROC)fnGetProcAddress("glUniform2ui64NV");
  pfn_glUniform3ui64NV = (PFNGLUNIFORM3UI64NVPROC)fnGetProcAddress("glUniform3ui64NV");
  pfn_glUniform4ui64NV = (PFNGLUNIFORM4UI64NVPROC)fnGetProcAddress("glUniform4ui64NV");
  pfn_glUniform1ui64vNV = (PFNGLUNIFORM1UI64VNVPROC)fnGetProcAddress("glUniform1ui64vNV");
  pfn_glUniform2ui64vNV = (PFNGLUNIFORM2UI64VNVPROC)fnGetProcAddress("glUniform2ui64vNV");
  pfn_glUniform3ui64vNV = (PFNGLUNIFORM3UI64VNVPROC)fnGetProcAddress("glUniform3ui64vNV");
  pfn_glUniform4ui64vNV = (PFNGLUNIFORM4UI64VNVPROC)fnGetProcAddress("glUniform4ui64vNV");
  pfn_glGetUniformi64vNV = (PFNGLGETUNIFORMI64VNVPROC)fnGetProcAddress("glGetUniformi64vNV");
  pfn_glProgramUniform1i64NV = (PFNGLPROGRAMUNIFORM1I64NVPROC)fnGetProcAddress("glProgramUniform1i64NV");
  pfn_glProgramUniform2i64NV = (PFNGLPROGRAMUNIFORM2I64NVPROC)fnGetProcAddress("glProgramUniform2i64NV");
  pfn_glProgramUniform3i64NV = (PFNGLPROGRAMUNIFORM3I64NVPROC)fnGetProcAddress("glProgramUniform3i64NV");
  pfn_glProgramUniform4i64NV = (PFNGLPROGRAMUNIFORM4I64NVPROC)fnGetProcAddress("glProgramUniform4i64NV");
  pfn_glProgramUniform1i64vNV = (PFNGLPROGRAMUNIFORM1I64VNVPROC)fnGetProcAddress("glProgramUniform1i64vNV");
  pfn_glProgramUniform2i64vNV = (PFNGLPROGRAMUNIFORM2I64VNVPROC)fnGetProcAddress("glProgramUniform2i64vNV");
  pfn_glProgramUniform3i64vNV = (PFNGLPROGRAMUNIFORM3I64VNVPROC)fnGetProcAddress("glProgramUniform3i64vNV");
  pfn_glProgramUniform4i64vNV = (PFNGLPROGRAMUNIFORM4I64VNVPROC)fnGetProcAddress("glProgramUniform4i64vNV");
  pfn_glProgramUniform1ui64NV = (PFNGLPROGRAMUNIFORM1UI64NVPROC)fnGetProcAddress("glProgramUniform1ui64NV");
  pfn_glProgramUniform2ui64NV = (PFNGLPROGRAMUNIFORM2UI64NVPROC)fnGetProcAddress("glProgramUniform2ui64NV");
  pfn_glProgramUniform3ui64NV = (PFNGLPROGRAMUNIFORM3UI64NVPROC)fnGetProcAddress("glProgramUniform3ui64NV");
  pfn_glProgramUniform4ui64NV = (PFNGLPROGRAMUNIFORM4UI64NVPROC)fnGetProcAddress("glProgramUniform4ui64NV");
  pfn_glProgramUniform1ui64vNV = (PFNGLPROGRAMUNIFORM1UI64VNVPROC)fnGetProcAddress("glProgramUniform1ui64vNV");
  pfn_glProgramUniform2ui64vNV = (PFNGLPROGRAMUNIFORM2UI64VNVPROC)fnGetProcAddress("glProgramUniform2ui64vNV");
  pfn_glProgramUniform3ui64vNV = (PFNGLPROGRAMUNIFORM3UI64VNVPROC)fnGetProcAddress("glProgramUniform3ui64vNV");
  pfn_glProgramUniform4ui64vNV = (PFNGLPROGRAMUNIFORM4UI64VNVPROC)fnGetProcAddress("glProgramUniform4ui64vNV");
  int success = has_extension("GL_NV_gpu_shader5");
  success = success && (pfn_glUniform1i64NV != 0);
  success = success && (pfn_glUniform2i64NV != 0);
  success = success && (pfn_glUniform3i64NV != 0);
  success = success && (pfn_glUniform4i64NV != 0);
  success = success && (pfn_glUniform1i64vNV != 0);
  success = success && (pfn_glUniform2i64vNV != 0);
  success = success && (pfn_glUniform3i64vNV != 0);
  success = success && (pfn_glUniform4i64vNV != 0);
  success = success && (pfn_glUniform1ui64NV != 0);
  success = success && (pfn_glUniform2ui64NV != 0);
  success = success && (pfn_glUniform3ui64NV != 0);
  success = success && (pfn_glUniform4ui64NV != 0);
  success = success && (pfn_glUniform1ui64vNV != 0);
  success = success && (pfn_glUniform2ui64vNV != 0);
  success = success && (pfn_glUniform3ui64vNV != 0);
  success = success && (pfn_glUniform4ui64vNV != 0);
  success = success && (pfn_glGetUniformi64vNV != 0);
  success = success && (pfn_glProgramUniform1i64NV != 0);
  success = success && (pfn_glProgramUniform2i64NV != 0);
  success = success && (pfn_glProgramUniform3i64NV != 0);
  success = success && (pfn_glProgramUniform4i64NV != 0);
  success = success && (pfn_glProgramUniform1i64vNV != 0);
  success = success && (pfn_glProgramUniform2i64vNV != 0);
  success = success && (pfn_glProgramUniform3i64vNV != 0);
  success = success && (pfn_glProgramUniform4i64vNV != 0);
  success = success && (pfn_glProgramUniform1ui64NV != 0);
  success = success && (pfn_glProgramUniform2ui64NV != 0);
  success = success && (pfn_glProgramUniform3ui64NV != 0);
  success = success && (pfn_glProgramUniform4ui64NV != 0);
  success = success && (pfn_glProgramUniform1ui64vNV != 0);
  success = success && (pfn_glProgramUniform2ui64vNV != 0);
  success = success && (pfn_glProgramUniform3ui64vNV != 0);
  success = success && (pfn_glProgramUniform4ui64vNV != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_internalformat_sample_query */

static PFNGLGETINTERNALFORMATSAMPLEIVNVPROC pfn_glGetInternalformatSampleivNV = 0;

GLAPI void APIENTRY glGetInternalformatSampleivNV(GLenum target, GLenum internalformat, GLsizei samples, GLenum pname, GLsizei bufSize, GLint* params)
{
  assert(pfn_glGetInternalformatSampleivNV);
  pfn_glGetInternalformatSampleivNV(target,internalformat,samples,pname,bufSize,params);
}

int load_GL_NV_internalformat_sample_query(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glGetInternalformatSampleivNV = (PFNGLGETINTERNALFORMATSAMPLEIVNVPROC)fnGetProcAddress("glGetInternalformatSampleivNV");
  int success = has_extension("GL_NV_internalformat_sample_query");
  success = success && (pfn_glGetInternalformatSampleivNV != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_memory_attachment */

static PFNGLGETMEMORYOBJECTDETACHEDRESOURCESUIVNVPROC pfn_glGetMemoryObjectDetachedResourcesuivNV = 0;
static PFNGLRESETMEMORYOBJECTPARAMETERNVPROC pfn_glResetMemoryObjectParameterNV = 0;
static PFNGLTEXATTACHMEMORYNVPROC pfn_glTexAttachMemoryNV = 0;
static PFNGLBUFFERATTACHMEMORYNVPROC pfn_glBufferAttachMemoryNV = 0;
static PFNGLTEXTUREATTACHMEMORYNVPROC pfn_glTextureAttachMemoryNV = 0;
static PFNGLNAMEDBUFFERATTACHMEMORYNVPROC pfn_glNamedBufferAttachMemoryNV = 0;

GLAPI void APIENTRY glGetMemoryObjectDetachedResourcesuivNV(GLuint memory, GLenum pname, GLint first, GLsizei count, GLuint* params)
{
  assert(pfn_glGetMemoryObjectDetachedResourcesuivNV);
  pfn_glGetMemoryObjectDetachedResourcesuivNV(memory,pname,first,count,params);
}
GLAPI void APIENTRY glResetMemoryObjectParameterNV(GLuint memory, GLenum pname)
{
  assert(pfn_glResetMemoryObjectParameterNV);
  pfn_glResetMemoryObjectParameterNV(memory,pname);
}
GLAPI void APIENTRY glTexAttachMemoryNV(GLenum target, GLuint memory, GLuint64 offset)
{
  assert(pfn_glTexAttachMemoryNV);
  pfn_glTexAttachMemoryNV(target,memory,offset);
}
GLAPI void APIENTRY glBufferAttachMemoryNV(GLenum target, GLuint memory, GLuint64 offset)
{
  assert(pfn_glBufferAttachMemoryNV);
  pfn_glBufferAttachMemoryNV(target,memory,offset);
}
GLAPI void APIENTRY glTextureAttachMemoryNV(GLuint texture, GLuint memory, GLuint64 offset)
{
  assert(pfn_glTextureAttachMemoryNV);
  pfn_glTextureAttachMemoryNV(texture,memory,offset);
}
GLAPI void APIENTRY glNamedBufferAttachMemoryNV(GLuint buffer, GLuint memory, GLuint64 offset)
{
  assert(pfn_glNamedBufferAttachMemoryNV);
  pfn_glNamedBufferAttachMemoryNV(buffer,memory,offset);
}

int load_GL_NV_memory_attachment(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glGetMemoryObjectDetachedResourcesuivNV = (PFNGLGETMEMORYOBJECTDETACHEDRESOURCESUIVNVPROC)fnGetProcAddress("glGetMemoryObjectDetachedResourcesuivNV");
  pfn_glResetMemoryObjectParameterNV = (PFNGLRESETMEMORYOBJECTPARAMETERNVPROC)fnGetProcAddress("glResetMemoryObjectParameterNV");
  pfn_glTexAttachMemoryNV = (PFNGLTEXATTACHMEMORYNVPROC)fnGetProcAddress("glTexAttachMemoryNV");
  pfn_glBufferAttachMemoryNV = (PFNGLBUFFERATTACHMEMORYNVPROC)fnGetProcAddress("glBufferAttachMemoryNV");
  pfn_glTextureAttachMemoryNV = (PFNGLTEXTUREATTACHMEMORYNVPROC)fnGetProcAddress("glTextureAttachMemoryNV");
  pfn_glNamedBufferAttachMemoryNV = (PFNGLNAMEDBUFFERATTACHMEMORYNVPROC)fnGetProcAddress("glNamedBufferAttachMemoryNV");
  int success = has_extension("GL_NV_memory_attachment");
  success = success && (pfn_glGetMemoryObjectDetachedResourcesuivNV != 0);
  success = success && (pfn_glResetMemoryObjectParameterNV != 0);
  success = success && (pfn_glTexAttachMemoryNV != 0);
  success = success && (pfn_glBufferAttachMemoryNV != 0);
  success = success && (pfn_glTextureAttachMemoryNV != 0);
  success = success && (pfn_glNamedBufferAttachMemoryNV != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_mesh_shader */

static PFNGLDRAWMESHTASKSNVPROC pfn_glDrawMeshTasksNV = 0;
static PFNGLDRAWMESHTASKSINDIRECTNVPROC pfn_glDrawMeshTasksIndirectNV = 0;
static PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC pfn_glMultiDrawMeshTasksIndirectNV = 0;
static PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC pfn_glMultiDrawMeshTasksIndirectCountNV = 0;

GLAPI void APIENTRY glDrawMeshTasksNV(GLuint first, GLuint count)
{
  assert(pfn_glDrawMeshTasksNV);
  pfn_glDrawMeshTasksNV(first,count);
}
GLAPI void APIENTRY glDrawMeshTasksIndirectNV(GLintptr indirect)
{
  assert(pfn_glDrawMeshTasksIndirectNV);
  pfn_glDrawMeshTasksIndirectNV(indirect);
}
GLAPI void APIENTRY glMultiDrawMeshTasksIndirectNV(GLintptr indirect, GLsizei drawcount, GLsizei stride)
{
  assert(pfn_glMultiDrawMeshTasksIndirectNV);
  pfn_glMultiDrawMeshTasksIndirectNV(indirect,drawcount,stride);
}
GLAPI void APIENTRY glMultiDrawMeshTasksIndirectCountNV(GLintptr indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride)
{
  assert(pfn_glMultiDrawMeshTasksIndirectCountNV);
  pfn_glMultiDrawMeshTasksIndirectCountNV(indirect,drawcount,maxdrawcount,stride);
}

int load_GL_NV_mesh_shader(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glDrawMeshTasksNV = (PFNGLDRAWMESHTASKSNVPROC)fnGetProcAddress("glDrawMeshTasksNV");
  pfn_glDrawMeshTasksIndirectNV = (PFNGLDRAWMESHTASKSINDIRECTNVPROC)fnGetProcAddress("glDrawMeshTasksIndirectNV");
  pfn_glMultiDrawMeshTasksIndirectNV = (PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC)fnGetProcAddress("glMultiDrawMeshTasksIndirectNV");
  pfn_glMultiDrawMeshTasksIndirectCountNV = (PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC)fnGetProcAddress("glMultiDrawMeshTasksIndirectCountNV");
  int success = has_extension("GL_NV_mesh_shader");
  success = success && (pfn_glDrawMeshTasksNV != 0);
  success = success && (pfn_glDrawMeshTasksIndirectNV != 0);
  success = success && (pfn_glMultiDrawMeshTasksIndirectNV != 0);
  success = success && (pfn_glMultiDrawMeshTasksIndirectCountNV != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_path_rendering */

static PFNGLGENPATHSNVPROC pfn_glGenPathsNV = 0;
static PFNGLDELETEPATHSNVPROC pfn_glDeletePathsNV = 0;
static PFNGLISPATHNVPROC pfn_glIsPathNV = 0;
static PFNGLPATHCOMMANDSNVPROC pfn_glPathCommandsNV = 0;
static PFNGLPATHCOORDSNVPROC pfn_glPathCoordsNV = 0;
static PFNGLPATHSUBCOMMANDSNVPROC pfn_glPathSubCommandsNV = 0;
static PFNGLPATHSUBCOORDSNVPROC pfn_glPathSubCoordsNV = 0;
static PFNGLPATHSTRINGNVPROC pfn_glPathStringNV = 0;
static PFNGLPATHGLYPHSNVPROC pfn_glPathGlyphsNV = 0;
static PFNGLPATHGLYPHRANGENVPROC pfn_glPathGlyphRangeNV = 0;
static PFNGLWEIGHTPATHSNVPROC pfn_glWeightPathsNV = 0;
static PFNGLCOPYPATHNVPROC pfn_glCopyPathNV = 0;
static PFNGLINTERPOLATEPATHSNVPROC pfn_glInterpolatePathsNV = 0;
static PFNGLTRANSFORMPATHNVPROC pfn_glTransformPathNV = 0;
static PFNGLPATHPARAMETERIVNVPROC pfn_glPathParameterivNV = 0;
static PFNGLPATHPARAMETERINVPROC pfn_glPathParameteriNV = 0;
static PFNGLPATHPARAMETERFVNVPROC pfn_glPathParameterfvNV = 0;
static PFNGLPATHPARAMETERFNVPROC pfn_glPathParameterfNV = 0;
static PFNGLPATHDASHARRAYNVPROC pfn_glPathDashArrayNV = 0;
static PFNGLPATHSTENCILFUNCNVPROC pfn_glPathStencilFuncNV = 0;
static PFNGLPATHSTENCILDEPTHOFFSETNVPROC pfn_glPathStencilDepthOffsetNV = 0;
static PFNGLSTENCILFILLPATHNVPROC pfn_glStencilFillPathNV = 0;
static PFNGLSTENCILSTROKEPATHNVPROC pfn_glStencilStrokePathNV = 0;
static PFNGLSTENCILFILLPATHINSTANCEDNVPROC pfn_glStencilFillPathInstancedNV = 0;
static PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC pfn_glStencilStrokePathInstancedNV = 0;
static PFNGLPATHCOVERDEPTHFUNCNVPROC pfn_glPathCoverDepthFuncNV = 0;
static PFNGLCOVERFILLPATHNVPROC pfn_glCoverFillPathNV = 0;
static PFNGLCOVERSTROKEPATHNVPROC pfn_glCoverStrokePathNV = 0;
static PFNGLCOVERFILLPATHINSTANCEDNVPROC pfn_glCoverFillPathInstancedNV = 0;
static PFNGLCOVERSTROKEPATHINSTANCEDNVPROC pfn_glCoverStrokePathInstancedNV = 0;
static PFNGLGETPATHPARAMETERIVNVPROC pfn_glGetPathParameterivNV = 0;
static PFNGLGETPATHPARAMETERFVNVPROC pfn_glGetPathParameterfvNV = 0;
static PFNGLGETPATHCOMMANDSNVPROC pfn_glGetPathCommandsNV = 0;
static PFNGLGETPATHCOORDSNVPROC pfn_glGetPathCoordsNV = 0;
static PFNGLGETPATHDASHARRAYNVPROC pfn_glGetPathDashArrayNV = 0;
static PFNGLGETPATHMETRICSNVPROC pfn_glGetPathMetricsNV = 0;
static PFNGLGETPATHMETRICRANGENVPROC pfn_glGetPathMetricRangeNV = 0;
static PFNGLGETPATHSPACINGNVPROC pfn_glGetPathSpacingNV = 0;
static PFNGLISPOINTINFILLPATHNVPROC pfn_glIsPointInFillPathNV = 0;
static PFNGLISPOINTINSTROKEPATHNVPROC pfn_glIsPointInStrokePathNV = 0;
static PFNGLGETPATHLENGTHNVPROC pfn_glGetPathLengthNV = 0;
static PFNGLPOINTALONGPATHNVPROC pfn_glPointAlongPathNV = 0;
static PFNGLMATRIXLOAD3X2FNVPROC pfn_glMatrixLoad3x2fNV = 0;
static PFNGLMATRIXLOAD3X3FNVPROC pfn_glMatrixLoad3x3fNV = 0;
static PFNGLMATRIXLOADTRANSPOSE3X3FNVPROC pfn_glMatrixLoadTranspose3x3fNV = 0;
static PFNGLMATRIXMULT3X2FNVPROC pfn_glMatrixMult3x2fNV = 0;
static PFNGLMATRIXMULT3X3FNVPROC pfn_glMatrixMult3x3fNV = 0;
static PFNGLMATRIXMULTTRANSPOSE3X3FNVPROC pfn_glMatrixMultTranspose3x3fNV = 0;
static PFNGLSTENCILTHENCOVERFILLPATHNVPROC pfn_glStencilThenCoverFillPathNV = 0;
static PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC pfn_glStencilThenCoverStrokePathNV = 0;
static PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC pfn_glStencilThenCoverFillPathInstancedNV = 0;
static PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC pfn_glStencilThenCoverStrokePathInstancedNV = 0;
static PFNGLPATHGLYPHINDEXRANGENVPROC pfn_glPathGlyphIndexRangeNV = 0;
static PFNGLPATHGLYPHINDEXARRAYNVPROC pfn_glPathGlyphIndexArrayNV = 0;
static PFNGLPATHMEMORYGLYPHINDEXARRAYNVPROC pfn_glPathMemoryGlyphIndexArrayNV = 0;
static PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC pfn_glProgramPathFragmentInputGenNV = 0;
static PFNGLGETPROGRAMRESOURCEFVNVPROC pfn_glGetProgramResourcefvNV = 0;

GLAPI GLuint APIENTRY glGenPathsNV(GLsizei range)
{
  assert(pfn_glGenPathsNV);
  return pfn_glGenPathsNV(range);
}
GLAPI void APIENTRY glDeletePathsNV(GLuint path, GLsizei range)
{
  assert(pfn_glDeletePathsNV);
  pfn_glDeletePathsNV(path,range);
}
GLAPI GLboolean APIENTRY glIsPathNV(GLuint path)
{
  assert(pfn_glIsPathNV);
  return pfn_glIsPathNV(path);
}
GLAPI void APIENTRY glPathCommandsNV(GLuint path, GLsizei numCommands, const GLubyte* commands, GLsizei numCoords, GLenum coordType, const void* coords)
{
  assert(pfn_glPathCommandsNV);
  pfn_glPathCommandsNV(path,numCommands,commands,numCoords,coordType,coords);
}
GLAPI void APIENTRY glPathCoordsNV(GLuint path, GLsizei numCoords, GLenum coordType, const void* coords)
{
  assert(pfn_glPathCoordsNV);
  pfn_glPathCoordsNV(path,numCoords,coordType,coords);
}
GLAPI void APIENTRY glPathSubCommandsNV(GLuint path, GLsizei commandStart, GLsizei commandsToDelete, GLsizei numCommands, const GLubyte* commands, GLsizei numCoords, GLenum coordType, const void* coords)
{
  assert(pfn_glPathSubCommandsNV);
  pfn_glPathSubCommandsNV(path,commandStart,commandsToDelete,numCommands,commands,numCoords,coordType,coords);
}
GLAPI void APIENTRY glPathSubCoordsNV(GLuint path, GLsizei coordStart, GLsizei numCoords, GLenum coordType, const void* coords)
{
  assert(pfn_glPathSubCoordsNV);
  pfn_glPathSubCoordsNV(path,coordStart,numCoords,coordType,coords);
}
GLAPI void APIENTRY glPathStringNV(GLuint path, GLenum format, GLsizei length, const void* pathString)
{
  assert(pfn_glPathStringNV);
  pfn_glPathStringNV(path,format,length,pathString);
}
GLAPI void APIENTRY glPathGlyphsNV(GLuint firstPathName, GLenum fontTarget, const void* fontName, GLbitfield fontStyle, GLsizei numGlyphs, GLenum type, const void* charcodes, GLenum handleMissingGlyphs, GLuint pathParameterTemplate, GLfloat emScale)
{
  assert(pfn_glPathGlyphsNV);
  pfn_glPathGlyphsNV(firstPathName,fontTarget,fontName,fontStyle,numGlyphs,type,charcodes,handleMissingGlyphs,pathParameterTemplate,emScale);
}
GLAPI void APIENTRY glPathGlyphRangeNV(GLuint firstPathName, GLenum fontTarget, const void* fontName, GLbitfield fontStyle, GLuint firstGlyph, GLsizei numGlyphs, GLenum handleMissingGlyphs, GLuint pathParameterTemplate, GLfloat emScale)
{
  assert(pfn_glPathGlyphRangeNV);
  pfn_glPathGlyphRangeNV(firstPathName,fontTarget,fontName,fontStyle,firstGlyph,numGlyphs,handleMissingGlyphs,pathParameterTemplate,emScale);
}
GLAPI void APIENTRY glWeightPathsNV(GLuint resultPath, GLsizei numPaths, const GLuint* paths, const GLfloat* weights)
{
  assert(pfn_glWeightPathsNV);
  pfn_glWeightPathsNV(resultPath,numPaths,paths,weights);
}
GLAPI void APIENTRY glCopyPathNV(GLuint resultPath, GLuint srcPath)
{
  assert(pfn_glCopyPathNV);
  pfn_glCopyPathNV(resultPath,srcPath);
}
GLAPI void APIENTRY glInterpolatePathsNV(GLuint resultPath, GLuint pathA, GLuint pathB, GLfloat weight)
{
  assert(pfn_glInterpolatePathsNV);
  pfn_glInterpolatePathsNV(resultPath,pathA,pathB,weight);
}
GLAPI void APIENTRY glTransformPathNV(GLuint resultPath, GLuint srcPath, GLenum transformType, const GLfloat* transformValues)
{
  assert(pfn_glTransformPathNV);
  pfn_glTransformPathNV(resultPath,srcPath,transformType,transformValues);
}
GLAPI void APIENTRY glPathParameterivNV(GLuint path, GLenum pname, const GLint* value)
{
  assert(pfn_glPathParameterivNV);
  pfn_glPathParameterivNV(path,pname,value);
}
GLAPI void APIENTRY glPathParameteriNV(GLuint path, GLenum pname, GLint value)
{
  assert(pfn_glPathParameteriNV);
  pfn_glPathParameteriNV(path,pname,value);
}
GLAPI void APIENTRY glPathParameterfvNV(GLuint path, GLenum pname, const GLfloat* value)
{
  assert(pfn_glPathParameterfvNV);
  pfn_glPathParameterfvNV(path,pname,value);
}
GLAPI void APIENTRY glPathParameterfNV(GLuint path, GLenum pname, GLfloat value)
{
  assert(pfn_glPathParameterfNV);
  pfn_glPathParameterfNV(path,pname,value);
}
GLAPI void APIENTRY glPathDashArrayNV(GLuint path, GLsizei dashCount, const GLfloat* dashArray)
{
  assert(pfn_glPathDashArrayNV);
  pfn_glPathDashArrayNV(path,dashCount,dashArray);
}
GLAPI void APIENTRY glPathStencilFuncNV(GLenum func, GLint ref, GLuint mask)
{
  assert(pfn_glPathStencilFuncNV);
  pfn_glPathStencilFuncNV(func,ref,mask);
}
GLAPI void APIENTRY glPathStencilDepthOffsetNV(GLfloat factor, GLfloat units)
{
  assert(pfn_glPathStencilDepthOffsetNV);
  pfn_glPathStencilDepthOffsetNV(factor,units);
}
GLAPI void APIENTRY glStencilFillPathNV(GLuint path, GLenum fillMode, GLuint mask)
{
  assert(pfn_glStencilFillPathNV);
  pfn_glStencilFillPathNV(path,fillMode,mask);
}
GLAPI void APIENTRY glStencilStrokePathNV(GLuint path, GLint reference, GLuint mask)
{
  assert(pfn_glStencilStrokePathNV);
  pfn_glStencilStrokePathNV(path,reference,mask);
}
GLAPI void APIENTRY glStencilFillPathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLenum fillMode, GLuint mask, GLenum transformType, const GLfloat* transformValues)
{
  assert(pfn_glStencilFillPathInstancedNV);
  pfn_glStencilFillPathInstancedNV(numPaths,pathNameType,paths,pathBase,fillMode,mask,transformType,transformValues);
}
GLAPI void APIENTRY glStencilStrokePathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLint reference, GLuint mask, GLenum transformType, const GLfloat* transformValues)
{
  assert(pfn_glStencilStrokePathInstancedNV);
  pfn_glStencilStrokePathInstancedNV(numPaths,pathNameType,paths,pathBase,reference,mask,transformType,transformValues);
}
GLAPI void APIENTRY glPathCoverDepthFuncNV(GLenum func)
{
  assert(pfn_glPathCoverDepthFuncNV);
  pfn_glPathCoverDepthFuncNV(func);
}
GLAPI void APIENTRY glCoverFillPathNV(GLuint path, GLenum coverMode)
{
  assert(pfn_glCoverFillPathNV);
  pfn_glCoverFillPathNV(path,coverMode);
}
GLAPI void APIENTRY glCoverStrokePathNV(GLuint path, GLenum coverMode)
{
  assert(pfn_glCoverStrokePathNV);
  pfn_glCoverStrokePathNV(path,coverMode);
}
GLAPI void APIENTRY glCoverFillPathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLenum coverMode, GLenum transformType, const GLfloat* transformValues)
{
  assert(pfn_glCoverFillPathInstancedNV);
  pfn_glCoverFillPathInstancedNV(numPaths,pathNameType,paths,pathBase,coverMode,transformType,transformValues);
}
GLAPI void APIENTRY glCoverStrokePathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLenum coverMode, GLenum transformType, const GLfloat* transformValues)
{
  assert(pfn_glCoverStrokePathInstancedNV);
  pfn_glCoverStrokePathInstancedNV(numPaths,pathNameType,paths,pathBase,coverMode,transformType,transformValues);
}
GLAPI void APIENTRY glGetPathParameterivNV(GLuint path, GLenum pname, GLint* value)
{
  assert(pfn_glGetPathParameterivNV);
  pfn_glGetPathParameterivNV(path,pname,value);
}
GLAPI void APIENTRY glGetPathParameterfvNV(GLuint path, GLenum pname, GLfloat* value)
{
  assert(pfn_glGetPathParameterfvNV);
  pfn_glGetPathParameterfvNV(path,pname,value);
}
GLAPI void APIENTRY glGetPathCommandsNV(GLuint path, GLubyte* commands)
{
  assert(pfn_glGetPathCommandsNV);
  pfn_glGetPathCommandsNV(path,commands);
}
GLAPI void APIENTRY glGetPathCoordsNV(GLuint path, GLfloat* coords)
{
  assert(pfn_glGetPathCoordsNV);
  pfn_glGetPathCoordsNV(path,coords);
}
GLAPI void APIENTRY glGetPathDashArrayNV(GLuint path, GLfloat* dashArray)
{
  assert(pfn_glGetPathDashArrayNV);
  pfn_glGetPathDashArrayNV(path,dashArray);
}
GLAPI void APIENTRY glGetPathMetricsNV(GLbitfield metricQueryMask, GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLsizei stride, GLfloat* metrics)
{
  assert(pfn_glGetPathMetricsNV);
  pfn_glGetPathMetricsNV(metricQueryMask,numPaths,pathNameType,paths,pathBase,stride,metrics);
}
GLAPI void APIENTRY glGetPathMetricRangeNV(GLbitfield metricQueryMask, GLuint firstPathName, GLsizei numPaths, GLsizei stride, GLfloat* metrics)
{
  assert(pfn_glGetPathMetricRangeNV);
  pfn_glGetPathMetricRangeNV(metricQueryMask,firstPathName,numPaths,stride,metrics);
}
GLAPI void APIENTRY glGetPathSpacingNV(GLenum pathListMode, GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLfloat advanceScale, GLfloat kerningScale, GLenum transformType, GLfloat* returnedSpacing)
{
  assert(pfn_glGetPathSpacingNV);
  pfn_glGetPathSpacingNV(pathListMode,numPaths,pathNameType,paths,pathBase,advanceScale,kerningScale,transformType,returnedSpacing);
}
GLAPI GLboolean APIENTRY glIsPointInFillPathNV(GLuint path, GLuint mask, GLfloat x, GLfloat y)
{
  assert(pfn_glIsPointInFillPathNV);
  return pfn_glIsPointInFillPathNV(path,mask,x,y);
}
GLAPI GLboolean APIENTRY glIsPointInStrokePathNV(GLuint path, GLfloat x, GLfloat y)
{
  assert(pfn_glIsPointInStrokePathNV);
  return pfn_glIsPointInStrokePathNV(path,x,y);
}
GLAPI GLfloat APIENTRY glGetPathLengthNV(GLuint path, GLsizei startSegment, GLsizei numSegments)
{
  assert(pfn_glGetPathLengthNV);
  return pfn_glGetPathLengthNV(path,startSegment,numSegments);
}
GLAPI GLboolean APIENTRY glPointAlongPathNV(GLuint path, GLsizei startSegment, GLsizei numSegments, GLfloat distance, GLfloat* x, GLfloat* y, GLfloat* tangentX, GLfloat* tangentY)
{
  assert(pfn_glPointAlongPathNV);
  return pfn_glPointAlongPathNV(path,startSegment,numSegments,distance,x,y,tangentX,tangentY);
}
GLAPI void APIENTRY glMatrixLoad3x2fNV(GLenum matrixMode, const GLfloat* m)
{
  assert(pfn_glMatrixLoad3x2fNV);
  pfn_glMatrixLoad3x2fNV(matrixMode,m);
}
GLAPI void APIENTRY glMatrixLoad3x3fNV(GLenum matrixMode, const GLfloat* m)
{
  assert(pfn_glMatrixLoad3x3fNV);
  pfn_glMatrixLoad3x3fNV(matrixMode,m);
}
GLAPI void APIENTRY glMatrixLoadTranspose3x3fNV(GLenum matrixMode, const GLfloat* m)
{
  assert(pfn_glMatrixLoadTranspose3x3fNV);
  pfn_glMatrixLoadTranspose3x3fNV(matrixMode,m);
}
GLAPI void APIENTRY glMatrixMult3x2fNV(GLenum matrixMode, const GLfloat* m)
{
  assert(pfn_glMatrixMult3x2fNV);
  pfn_glMatrixMult3x2fNV(matrixMode,m);
}
GLAPI void APIENTRY glMatrixMult3x3fNV(GLenum matrixMode, const GLfloat* m)
{
  assert(pfn_glMatrixMult3x3fNV);
  pfn_glMatrixMult3x3fNV(matrixMode,m);
}
GLAPI void APIENTRY glMatrixMultTranspose3x3fNV(GLenum matrixMode, const GLfloat* m)
{
  assert(pfn_glMatrixMultTranspose3x3fNV);
  pfn_glMatrixMultTranspose3x3fNV(matrixMode,m);
}
GLAPI void APIENTRY glStencilThenCoverFillPathNV(GLuint path, GLenum fillMode, GLuint mask, GLenum coverMode)
{
  assert(pfn_glStencilThenCoverFillPathNV);
  pfn_glStencilThenCoverFillPathNV(path,fillMode,mask,coverMode);
}
GLAPI void APIENTRY glStencilThenCoverStrokePathNV(GLuint path, GLint reference, GLuint mask, GLenum coverMode)
{
  assert(pfn_glStencilThenCoverStrokePathNV);
  pfn_glStencilThenCoverStrokePathNV(path,reference,mask,coverMode);
}
GLAPI void APIENTRY glStencilThenCoverFillPathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLenum fillMode, GLuint mask, GLenum coverMode, GLenum transformType, const GLfloat* transformValues)
{
  assert(pfn_glStencilThenCoverFillPathInstancedNV);
  pfn_glStencilThenCoverFillPathInstancedNV(numPaths,pathNameType,paths,pathBase,fillMode,mask,coverMode,transformType,transformValues);
}
GLAPI void APIENTRY glStencilThenCoverStrokePathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void* paths, GLuint pathBase, GLint reference, GLuint mask, GLenum coverMode, GLenum transformType, const GLfloat* transformValues)
{
  assert(pfn_glStencilThenCoverStrokePathInstancedNV);
  pfn_glStencilThenCoverStrokePathInstancedNV(numPaths,pathNameType,paths,pathBase,reference,mask,coverMode,transformType,transformValues);
}
GLAPI GLenum APIENTRY glPathGlyphIndexRangeNV(GLenum fontTarget, const void* fontName, GLbitfield fontStyle, GLuint pathParameterTemplate, GLfloat emScale, GLuint baseAndCount[2])
{
  assert(pfn_glPathGlyphIndexRangeNV);
  return pfn_glPathGlyphIndexRangeNV(fontTarget,fontName,fontStyle,pathParameterTemplate,emScale,baseAndCount);
}
GLAPI GLenum APIENTRY glPathGlyphIndexArrayNV(GLuint firstPathName, GLenum fontTarget, const void* fontName, GLbitfield fontStyle, GLuint firstGlyphIndex, GLsizei numGlyphs, GLuint pathParameterTemplate, GLfloat emScale)
{
  assert(pfn_glPathGlyphIndexArrayNV);
  return pfn_glPathGlyphIndexArrayNV(firstPathName,fontTarget,fontName,fontStyle,firstGlyphIndex,numGlyphs,pathParameterTemplate,emScale);
}
GLAPI GLenum APIENTRY glPathMemoryGlyphIndexArrayNV(GLuint firstPathName, GLenum fontTarget, GLsizeiptr fontSize, const void* fontData, GLsizei faceIndex, GLuint firstGlyphIndex, GLsizei numGlyphs, GLuint pathParameterTemplate, GLfloat emScale)
{
  assert(pfn_glPathMemoryGlyphIndexArrayNV);
  return pfn_glPathMemoryGlyphIndexArrayNV(firstPathName,fontTarget,fontSize,fontData,faceIndex,firstGlyphIndex,numGlyphs,pathParameterTemplate,emScale);
}
GLAPI void APIENTRY glProgramPathFragmentInputGenNV(GLuint program, GLint location, GLenum genMode, GLint components, const GLfloat* coeffs)
{
  assert(pfn_glProgramPathFragmentInputGenNV);
  pfn_glProgramPathFragmentInputGenNV(program,location,genMode,components,coeffs);
}
GLAPI void APIENTRY glGetProgramResourcefvNV(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum* props, GLsizei bufSize, GLsizei* length, GLfloat* params)
{
  assert(pfn_glGetProgramResourcefvNV);
  pfn_glGetProgramResourcefvNV(program,programInterface,index,propCount,props,bufSize,length,params);
}

int load_GL_NV_path_rendering(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glGenPathsNV = (PFNGLGENPATHSNVPROC)fnGetProcAddress("glGenPathsNV");
  pfn_glDeletePathsNV = (PFNGLDELETEPATHSNVPROC)fnGetProcAddress("glDeletePathsNV");
  pfn_glIsPathNV = (PFNGLISPATHNVPROC)fnGetProcAddress("glIsPathNV");
  pfn_glPathCommandsNV = (PFNGLPATHCOMMANDSNVPROC)fnGetProcAddress("glPathCommandsNV");
  pfn_glPathCoordsNV = (PFNGLPATHCOORDSNVPROC)fnGetProcAddress("glPathCoordsNV");
  pfn_glPathSubCommandsNV = (PFNGLPATHSUBCOMMANDSNVPROC)fnGetProcAddress("glPathSubCommandsNV");
  pfn_glPathSubCoordsNV = (PFNGLPATHSUBCOORDSNVPROC)fnGetProcAddress("glPathSubCoordsNV");
  pfn_glPathStringNV = (PFNGLPATHSTRINGNVPROC)fnGetProcAddress("glPathStringNV");
  pfn_glPathGlyphsNV = (PFNGLPATHGLYPHSNVPROC)fnGetProcAddress("glPathGlyphsNV");
  pfn_glPathGlyphRangeNV = (PFNGLPATHGLYPHRANGENVPROC)fnGetProcAddress("glPathGlyphRangeNV");
  pfn_glWeightPathsNV = (PFNGLWEIGHTPATHSNVPROC)fnGetProcAddress("glWeightPathsNV");
  pfn_glCopyPathNV = (PFNGLCOPYPATHNVPROC)fnGetProcAddress("glCopyPathNV");
  pfn_glInterpolatePathsNV = (PFNGLINTERPOLATEPATHSNVPROC)fnGetProcAddress("glInterpolatePathsNV");
  pfn_glTransformPathNV = (PFNGLTRANSFORMPATHNVPROC)fnGetProcAddress("glTransformPathNV");
  pfn_glPathParameterivNV = (PFNGLPATHPARAMETERIVNVPROC)fnGetProcAddress("glPathParameterivNV");
  pfn_glPathParameteriNV = (PFNGLPATHPARAMETERINVPROC)fnGetProcAddress("glPathParameteriNV");
  pfn_glPathParameterfvNV = (PFNGLPATHPARAMETERFVNVPROC)fnGetProcAddress("glPathParameterfvNV");
  pfn_glPathParameterfNV = (PFNGLPATHPARAMETERFNVPROC)fnGetProcAddress("glPathParameterfNV");
  pfn_glPathDashArrayNV = (PFNGLPATHDASHARRAYNVPROC)fnGetProcAddress("glPathDashArrayNV");
  pfn_glPathStencilFuncNV = (PFNGLPATHSTENCILFUNCNVPROC)fnGetProcAddress("glPathStencilFuncNV");
  pfn_glPathStencilDepthOffsetNV = (PFNGLPATHSTENCILDEPTHOFFSETNVPROC)fnGetProcAddress("glPathStencilDepthOffsetNV");
  pfn_glStencilFillPathNV = (PFNGLSTENCILFILLPATHNVPROC)fnGetProcAddress("glStencilFillPathNV");
  pfn_glStencilStrokePathNV = (PFNGLSTENCILSTROKEPATHNVPROC)fnGetProcAddress("glStencilStrokePathNV");
  pfn_glStencilFillPathInstancedNV = (PFNGLSTENCILFILLPATHINSTANCEDNVPROC)fnGetProcAddress("glStencilFillPathInstancedNV");
  pfn_glStencilStrokePathInstancedNV = (PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC)fnGetProcAddress("glStencilStrokePathInstancedNV");
  pfn_glPathCoverDepthFuncNV = (PFNGLPATHCOVERDEPTHFUNCNVPROC)fnGetProcAddress("glPathCoverDepthFuncNV");
  pfn_glCoverFillPathNV = (PFNGLCOVERFILLPATHNVPROC)fnGetProcAddress("glCoverFillPathNV");
  pfn_glCoverStrokePathNV = (PFNGLCOVERSTROKEPATHNVPROC)fnGetProcAddress("glCoverStrokePathNV");
  pfn_glCoverFillPathInstancedNV = (PFNGLCOVERFILLPATHINSTANCEDNVPROC)fnGetProcAddress("glCoverFillPathInstancedNV");
  pfn_glCoverStrokePathInstancedNV = (PFNGLCOVERSTROKEPATHINSTANCEDNVPROC)fnGetProcAddress("glCoverStrokePathInstancedNV");
  pfn_glGetPathParameterivNV = (PFNGLGETPATHPARAMETERIVNVPROC)fnGetProcAddress("glGetPathParameterivNV");
  pfn_glGetPathParameterfvNV = (PFNGLGETPATHPARAMETERFVNVPROC)fnGetProcAddress("glGetPathParameterfvNV");
  pfn_glGetPathCommandsNV = (PFNGLGETPATHCOMMANDSNVPROC)fnGetProcAddress("glGetPathCommandsNV");
  pfn_glGetPathCoordsNV = (PFNGLGETPATHCOORDSNVPROC)fnGetProcAddress("glGetPathCoordsNV");
  pfn_glGetPathDashArrayNV = (PFNGLGETPATHDASHARRAYNVPROC)fnGetProcAddress("glGetPathDashArrayNV");
  pfn_glGetPathMetricsNV = (PFNGLGETPATHMETRICSNVPROC)fnGetProcAddress("glGetPathMetricsNV");
  pfn_glGetPathMetricRangeNV = (PFNGLGETPATHMETRICRANGENVPROC)fnGetProcAddress("glGetPathMetricRangeNV");
  pfn_glGetPathSpacingNV = (PFNGLGETPATHSPACINGNVPROC)fnGetProcAddress("glGetPathSpacingNV");
  pfn_glIsPointInFillPathNV = (PFNGLISPOINTINFILLPATHNVPROC)fnGetProcAddress("glIsPointInFillPathNV");
  pfn_glIsPointInStrokePathNV = (PFNGLISPOINTINSTROKEPATHNVPROC)fnGetProcAddress("glIsPointInStrokePathNV");
  pfn_glGetPathLengthNV = (PFNGLGETPATHLENGTHNVPROC)fnGetProcAddress("glGetPathLengthNV");
  pfn_glPointAlongPathNV = (PFNGLPOINTALONGPATHNVPROC)fnGetProcAddress("glPointAlongPathNV");
  pfn_glMatrixLoad3x2fNV = (PFNGLMATRIXLOAD3X2FNVPROC)fnGetProcAddress("glMatrixLoad3x2fNV");
  pfn_glMatrixLoad3x3fNV = (PFNGLMATRIXLOAD3X3FNVPROC)fnGetProcAddress("glMatrixLoad3x3fNV");
  pfn_glMatrixLoadTranspose3x3fNV = (PFNGLMATRIXLOADTRANSPOSE3X3FNVPROC)fnGetProcAddress("glMatrixLoadTranspose3x3fNV");
  pfn_glMatrixMult3x2fNV = (PFNGLMATRIXMULT3X2FNVPROC)fnGetProcAddress("glMatrixMult3x2fNV");
  pfn_glMatrixMult3x3fNV = (PFNGLMATRIXMULT3X3FNVPROC)fnGetProcAddress("glMatrixMult3x3fNV");
  pfn_glMatrixMultTranspose3x3fNV = (PFNGLMATRIXMULTTRANSPOSE3X3FNVPROC)fnGetProcAddress("glMatrixMultTranspose3x3fNV");
  pfn_glStencilThenCoverFillPathNV = (PFNGLSTENCILTHENCOVERFILLPATHNVPROC)fnGetProcAddress("glStencilThenCoverFillPathNV");
  pfn_glStencilThenCoverStrokePathNV = (PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC)fnGetProcAddress("glStencilThenCoverStrokePathNV");
  pfn_glStencilThenCoverFillPathInstancedNV = (PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC)fnGetProcAddress("glStencilThenCoverFillPathInstancedNV");
  pfn_glStencilThenCoverStrokePathInstancedNV = (PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC)fnGetProcAddress("glStencilThenCoverStrokePathInstancedNV");
  pfn_glPathGlyphIndexRangeNV = (PFNGLPATHGLYPHINDEXRANGENVPROC)fnGetProcAddress("glPathGlyphIndexRangeNV");
  pfn_glPathGlyphIndexArrayNV = (PFNGLPATHGLYPHINDEXARRAYNVPROC)fnGetProcAddress("glPathGlyphIndexArrayNV");
  pfn_glPathMemoryGlyphIndexArrayNV = (PFNGLPATHMEMORYGLYPHINDEXARRAYNVPROC)fnGetProcAddress("glPathMemoryGlyphIndexArrayNV");
  pfn_glProgramPathFragmentInputGenNV = (PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC)fnGetProcAddress("glProgramPathFragmentInputGenNV");
  pfn_glGetProgramResourcefvNV = (PFNGLGETPROGRAMRESOURCEFVNVPROC)fnGetProcAddress("glGetProgramResourcefvNV");
  int success = has_extension("GL_NV_path_rendering");
  success = success && (pfn_glGenPathsNV != 0);
  success = success && (pfn_glDeletePathsNV != 0);
  success = success && (pfn_glIsPathNV != 0);
  success = success && (pfn_glPathCommandsNV != 0);
  success = success && (pfn_glPathCoordsNV != 0);
  success = success && (pfn_glPathSubCommandsNV != 0);
  success = success && (pfn_glPathSubCoordsNV != 0);
  success = success && (pfn_glPathStringNV != 0);
  success = success && (pfn_glPathGlyphsNV != 0);
  success = success && (pfn_glPathGlyphRangeNV != 0);
  success = success && (pfn_glWeightPathsNV != 0);
  success = success && (pfn_glCopyPathNV != 0);
  success = success && (pfn_glInterpolatePathsNV != 0);
  success = success && (pfn_glTransformPathNV != 0);
  success = success && (pfn_glPathParameterivNV != 0);
  success = success && (pfn_glPathParameteriNV != 0);
  success = success && (pfn_glPathParameterfvNV != 0);
  success = success && (pfn_glPathParameterfNV != 0);
  success = success && (pfn_glPathDashArrayNV != 0);
  success = success && (pfn_glPathStencilFuncNV != 0);
  success = success && (pfn_glPathStencilDepthOffsetNV != 0);
  success = success && (pfn_glStencilFillPathNV != 0);
  success = success && (pfn_glStencilStrokePathNV != 0);
  success = success && (pfn_glStencilFillPathInstancedNV != 0);
  success = success && (pfn_glStencilStrokePathInstancedNV != 0);
  success = success && (pfn_glPathCoverDepthFuncNV != 0);
  success = success && (pfn_glCoverFillPathNV != 0);
  success = success && (pfn_glCoverStrokePathNV != 0);
  success = success && (pfn_glCoverFillPathInstancedNV != 0);
  success = success && (pfn_glCoverStrokePathInstancedNV != 0);
  success = success && (pfn_glGetPathParameterivNV != 0);
  success = success && (pfn_glGetPathParameterfvNV != 0);
  success = success && (pfn_glGetPathCommandsNV != 0);
  success = success && (pfn_glGetPathCoordsNV != 0);
  success = success && (pfn_glGetPathDashArrayNV != 0);
  success = success && (pfn_glGetPathMetricsNV != 0);
  success = success && (pfn_glGetPathMetricRangeNV != 0);
  success = success && (pfn_glGetPathSpacingNV != 0);
  success = success && (pfn_glIsPointInFillPathNV != 0);
  success = success && (pfn_glIsPointInStrokePathNV != 0);
  success = success && (pfn_glGetPathLengthNV != 0);
  success = success && (pfn_glPointAlongPathNV != 0);
  success = success && (pfn_glMatrixLoad3x2fNV != 0);
  success = success && (pfn_glMatrixLoad3x3fNV != 0);
  success = success && (pfn_glMatrixLoadTranspose3x3fNV != 0);
  success = success && (pfn_glMatrixMult3x2fNV != 0);
  success = success && (pfn_glMatrixMult3x3fNV != 0);
  success = success && (pfn_glMatrixMultTranspose3x3fNV != 0);
  success = success && (pfn_glStencilThenCoverFillPathNV != 0);
  success = success && (pfn_glStencilThenCoverStrokePathNV != 0);
  success = success && (pfn_glStencilThenCoverFillPathInstancedNV != 0);
  success = success && (pfn_glStencilThenCoverStrokePathInstancedNV != 0);
  success = success && (pfn_glPathGlyphIndexRangeNV != 0);
  success = success && (pfn_glPathGlyphIndexArrayNV != 0);
  success = success && (pfn_glPathMemoryGlyphIndexArrayNV != 0);
  success = success && (pfn_glProgramPathFragmentInputGenNV != 0);
  success = success && (pfn_glGetProgramResourcefvNV != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_representative_fragment_test */



int load_GL_NV_representative_fragment_test(nvGLLoaderGetProcFN fnGetProcAddress)
{
  int success = has_extension("GL_NV_representative_fragment_test");
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_sample_locations */

static PFNGLFRAMEBUFFERSAMPLELOCATIONSFVNVPROC pfn_glFramebufferSampleLocationsfvNV = 0;
static PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVNVPROC pfn_glNamedFramebufferSampleLocationsfvNV = 0;
static PFNGLRESOLVEDEPTHVALUESNVPROC pfn_glResolveDepthValuesNV = 0;

GLAPI void APIENTRY glFramebufferSampleLocationsfvNV(GLenum target, GLuint start, GLsizei count, const GLfloat* v)
{
  assert(pfn_glFramebufferSampleLocationsfvNV);
  pfn_glFramebufferSampleLocationsfvNV(target,start,count,v);
}
GLAPI void APIENTRY glNamedFramebufferSampleLocationsfvNV(GLuint framebuffer, GLuint start, GLsizei count, const GLfloat* v)
{
  assert(pfn_glNamedFramebufferSampleLocationsfvNV);
  pfn_glNamedFramebufferSampleLocationsfvNV(framebuffer,start,count,v);
}
GLAPI void APIENTRY glResolveDepthValuesNV(void)
{
  assert(pfn_glResolveDepthValuesNV);
  pfn_glResolveDepthValuesNV();
}

int load_GL_NV_sample_locations(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glFramebufferSampleLocationsfvNV = (PFNGLFRAMEBUFFERSAMPLELOCATIONSFVNVPROC)fnGetProcAddress("glFramebufferSampleLocationsfvNV");
  pfn_glNamedFramebufferSampleLocationsfvNV = (PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVNVPROC)fnGetProcAddress("glNamedFramebufferSampleLocationsfvNV");
  pfn_glResolveDepthValuesNV = (PFNGLRESOLVEDEPTHVALUESNVPROC)fnGetProcAddress("glResolveDepthValuesNV");
  int success = has_extension("GL_NV_sample_locations");
  success = success && (pfn_glFramebufferSampleLocationsfvNV != 0);
  success = success && (pfn_glNamedFramebufferSampleLocationsfvNV != 0);
  success = success && (pfn_glResolveDepthValuesNV != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_sample_mask_override_coverage */



int load_GL_NV_sample_mask_override_coverage(nvGLLoaderGetProcFN fnGetProcAddress)
{
  int success = has_extension("GL_NV_sample_mask_override_coverage");
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_scissor_exclusive */

static PFNGLSCISSOREXCLUSIVENVPROC pfn_glScissorExclusiveNV = 0;
static PFNGLSCISSOREXCLUSIVEARRAYVNVPROC pfn_glScissorExclusiveArrayvNV = 0;

GLAPI void APIENTRY glScissorExclusiveNV(GLint x, GLint y, GLsizei width, GLsizei height)
{
  assert(pfn_glScissorExclusiveNV);
  pfn_glScissorExclusiveNV(x,y,width,height);
}
GLAPI void APIENTRY glScissorExclusiveArrayvNV(GLuint first, GLsizei count, const GLint* v)
{
  assert(pfn_glScissorExclusiveArrayvNV);
  pfn_glScissorExclusiveArrayvNV(first,count,v);
}

int load_GL_NV_scissor_exclusive(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glScissorExclusiveNV = (PFNGLSCISSOREXCLUSIVENVPROC)fnGetProcAddress("glScissorExclusiveNV");
  pfn_glScissorExclusiveArrayvNV = (PFNGLSCISSOREXCLUSIVEARRAYVNVPROC)fnGetProcAddress("glScissorExclusiveArrayvNV");
  int success = has_extension("GL_NV_scissor_exclusive");
  success = success && (pfn_glScissorExclusiveNV != 0);
  success = success && (pfn_glScissorExclusiveArrayvNV != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_shader_atomic_int64 */



int load_GL_NV_shader_atomic_int64(nvGLLoaderGetProcFN fnGetProcAddress)
{
  int success = has_extension("GL_NV_shader_atomic_int64");
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_shader_buffer_load */

static PFNGLMAKEBUFFERRESIDENTNVPROC pfn_glMakeBufferResidentNV = 0;
static PFNGLMAKEBUFFERNONRESIDENTNVPROC pfn_glMakeBufferNonResidentNV = 0;
static PFNGLISBUFFERRESIDENTNVPROC pfn_glIsBufferResidentNV = 0;
static PFNGLMAKENAMEDBUFFERRESIDENTNVPROC pfn_glMakeNamedBufferResidentNV = 0;
static PFNGLMAKENAMEDBUFFERNONRESIDENTNVPROC pfn_glMakeNamedBufferNonResidentNV = 0;
static PFNGLISNAMEDBUFFERRESIDENTNVPROC pfn_glIsNamedBufferResidentNV = 0;
static PFNGLGETBUFFERPARAMETERUI64VNVPROC pfn_glGetBufferParameterui64vNV = 0;
static PFNGLGETNAMEDBUFFERPARAMETERUI64VNVPROC pfn_glGetNamedBufferParameterui64vNV = 0;
static PFNGLGETINTEGERUI64VNVPROC pfn_glGetIntegerui64vNV = 0;
static PFNGLUNIFORMUI64NVPROC pfn_glUniformui64NV = 0;
static PFNGLUNIFORMUI64VNVPROC pfn_glUniformui64vNV = 0;
static PFNGLGETUNIFORMUI64VNVPROC pfn_glGetUniformui64vNV = 0;
static PFNGLPROGRAMUNIFORMUI64NVPROC pfn_glProgramUniformui64NV = 0;
static PFNGLPROGRAMUNIFORMUI64VNVPROC pfn_glProgramUniformui64vNV = 0;

GLAPI void APIENTRY glMakeBufferResidentNV(GLenum target, GLenum access)
{
  assert(pfn_glMakeBufferResidentNV);
  pfn_glMakeBufferResidentNV(target,access);
}
GLAPI void APIENTRY glMakeBufferNonResidentNV(GLenum target)
{
  assert(pfn_glMakeBufferNonResidentNV);
  pfn_glMakeBufferNonResidentNV(target);
}
GLAPI GLboolean APIENTRY glIsBufferResidentNV(GLenum target)
{
  assert(pfn_glIsBufferResidentNV);
  return pfn_glIsBufferResidentNV(target);
}
GLAPI void APIENTRY glMakeNamedBufferResidentNV(GLuint buffer, GLenum access)
{
  assert(pfn_glMakeNamedBufferResidentNV);
  pfn_glMakeNamedBufferResidentNV(buffer,access);
}
GLAPI void APIENTRY glMakeNamedBufferNonResidentNV(GLuint buffer)
{
  assert(pfn_glMakeNamedBufferNonResidentNV);
  pfn_glMakeNamedBufferNonResidentNV(buffer);
}
GLAPI GLboolean APIENTRY glIsNamedBufferResidentNV(GLuint buffer)
{
  assert(pfn_glIsNamedBufferResidentNV);
  return pfn_glIsNamedBufferResidentNV(buffer);
}
GLAPI void APIENTRY glGetBufferParameterui64vNV(GLenum target, GLenum pname, GLuint64EXT* params)
{
  assert(pfn_glGetBufferParameterui64vNV);
  pfn_glGetBufferParameterui64vNV(target,pname,params);
}
GLAPI void APIENTRY glGetNamedBufferParameterui64vNV(GLuint buffer, GLenum pname, GLuint64EXT* params)
{
  assert(pfn_glGetNamedBufferParameterui64vNV);
  pfn_glGetNamedBufferParameterui64vNV(buffer,pname,params);
}
GLAPI void APIENTRY glGetIntegerui64vNV(GLenum value, GLuint64EXT* result)
{
  assert(pfn_glGetIntegerui64vNV);
  pfn_glGetIntegerui64vNV(value,result);
}
GLAPI void APIENTRY glUniformui64NV(GLint location, GLuint64EXT value)
{
  assert(pfn_glUniformui64NV);
  pfn_glUniformui64NV(location,value);
}
GLAPI void APIENTRY glUniformui64vNV(GLint location, GLsizei count, const GLuint64EXT* value)
{
  assert(pfn_glUniformui64vNV);
  pfn_glUniformui64vNV(location,count,value);
}
GLAPI void APIENTRY glGetUniformui64vNV(GLuint program, GLint location, GLuint64EXT* params)
{
  assert(pfn_glGetUniformui64vNV);
  pfn_glGetUniformui64vNV(program,location,params);
}
GLAPI void APIENTRY glProgramUniformui64NV(GLuint program, GLint location, GLuint64EXT value)
{
  assert(pfn_glProgramUniformui64NV);
  pfn_glProgramUniformui64NV(program,location,value);
}
GLAPI void APIENTRY glProgramUniformui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64EXT* value)
{
  assert(pfn_glProgramUniformui64vNV);
  pfn_glProgramUniformui64vNV(program,location,count,value);
}

int load_GL_NV_shader_buffer_load(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glMakeBufferResidentNV = (PFNGLMAKEBUFFERRESIDENTNVPROC)fnGetProcAddress("glMakeBufferResidentNV");
  pfn_glMakeBufferNonResidentNV = (PFNGLMAKEBUFFERNONRESIDENTNVPROC)fnGetProcAddress("glMakeBufferNonResidentNV");
  pfn_glIsBufferResidentNV = (PFNGLISBUFFERRESIDENTNVPROC)fnGetProcAddress("glIsBufferResidentNV");
  pfn_glMakeNamedBufferResidentNV = (PFNGLMAKENAMEDBUFFERRESIDENTNVPROC)fnGetProcAddress("glMakeNamedBufferResidentNV");
  pfn_glMakeNamedBufferNonResidentNV = (PFNGLMAKENAMEDBUFFERNONRESIDENTNVPROC)fnGetProcAddress("glMakeNamedBufferNonResidentNV");
  pfn_glIsNamedBufferResidentNV = (PFNGLISNAMEDBUFFERRESIDENTNVPROC)fnGetProcAddress("glIsNamedBufferResidentNV");
  pfn_glGetBufferParameterui64vNV = (PFNGLGETBUFFERPARAMETERUI64VNVPROC)fnGetProcAddress("glGetBufferParameterui64vNV");
  pfn_glGetNamedBufferParameterui64vNV = (PFNGLGETNAMEDBUFFERPARAMETERUI64VNVPROC)fnGetProcAddress("glGetNamedBufferParameterui64vNV");
  pfn_glGetIntegerui64vNV = (PFNGLGETINTEGERUI64VNVPROC)fnGetProcAddress("glGetIntegerui64vNV");
  pfn_glUniformui64NV = (PFNGLUNIFORMUI64NVPROC)fnGetProcAddress("glUniformui64NV");
  pfn_glUniformui64vNV = (PFNGLUNIFORMUI64VNVPROC)fnGetProcAddress("glUniformui64vNV");
  pfn_glGetUniformui64vNV = (PFNGLGETUNIFORMUI64VNVPROC)fnGetProcAddress("glGetUniformui64vNV");
  pfn_glProgramUniformui64NV = (PFNGLPROGRAMUNIFORMUI64NVPROC)fnGetProcAddress("glProgramUniformui64NV");
  pfn_glProgramUniformui64vNV = (PFNGLPROGRAMUNIFORMUI64VNVPROC)fnGetProcAddress("glProgramUniformui64vNV");
  int success = has_extension("GL_NV_shader_buffer_load");
  success = success && (pfn_glMakeBufferResidentNV != 0);
  success = success && (pfn_glMakeBufferNonResidentNV != 0);
  success = success && (pfn_glIsBufferResidentNV != 0);
  success = success && (pfn_glMakeNamedBufferResidentNV != 0);
  success = success && (pfn_glMakeNamedBufferNonResidentNV != 0);
  success = success && (pfn_glIsNamedBufferResidentNV != 0);
  success = success && (pfn_glGetBufferParameterui64vNV != 0);
  success = success && (pfn_glGetNamedBufferParameterui64vNV != 0);
  success = success && (pfn_glGetIntegerui64vNV != 0);
  success = success && (pfn_glUniformui64NV != 0);
  success = success && (pfn_glUniformui64vNV != 0);
  success = success && (pfn_glGetUniformui64vNV != 0);
  success = success && (pfn_glProgramUniformui64NV != 0);
  success = success && (pfn_glProgramUniformui64vNV != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_shader_buffer_store */



int load_GL_NV_shader_buffer_store(nvGLLoaderGetProcFN fnGetProcAddress)
{
  int success = has_extension("GL_NV_shader_buffer_store");
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_shader_texture_footprint */



int load_GL_NV_shader_texture_footprint(nvGLLoaderGetProcFN fnGetProcAddress)
{
  int success = has_extension("GL_NV_shader_texture_footprint");
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_shader_thread_group */



int load_GL_NV_shader_thread_group(nvGLLoaderGetProcFN fnGetProcAddress)
{
  int success = has_extension("GL_NV_shader_thread_group");
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_shader_thread_shuffle */



int load_GL_NV_shader_thread_shuffle(nvGLLoaderGetProcFN fnGetProcAddress)
{
  int success = has_extension("GL_NV_shader_thread_shuffle");
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_shading_rate_image */

static PFNGLBINDSHADINGRATEIMAGENVPROC pfn_glBindShadingRateImageNV = 0;
static PFNGLGETSHADINGRATEIMAGEPALETTENVPROC pfn_glGetShadingRateImagePaletteNV = 0;
static PFNGLGETSHADINGRATESAMPLELOCATIONIVNVPROC pfn_glGetShadingRateSampleLocationivNV = 0;
static PFNGLSHADINGRATEIMAGEBARRIERNVPROC pfn_glShadingRateImageBarrierNV = 0;
static PFNGLSHADINGRATEIMAGEPALETTENVPROC pfn_glShadingRateImagePaletteNV = 0;
static PFNGLSHADINGRATESAMPLEORDERNVPROC pfn_glShadingRateSampleOrderNV = 0;
static PFNGLSHADINGRATESAMPLEORDERCUSTOMNVPROC pfn_glShadingRateSampleOrderCustomNV = 0;

GLAPI void APIENTRY glBindShadingRateImageNV(GLuint texture)
{
  assert(pfn_glBindShadingRateImageNV);
  pfn_glBindShadingRateImageNV(texture);
}
GLAPI void APIENTRY glGetShadingRateImagePaletteNV(GLuint viewport, GLuint entry, GLenum* rate)
{
  assert(pfn_glGetShadingRateImagePaletteNV);
  pfn_glGetShadingRateImagePaletteNV(viewport,entry,rate);
}
GLAPI void APIENTRY glGetShadingRateSampleLocationivNV(GLenum rate, GLuint samples, GLuint index, GLint* location)
{
  assert(pfn_glGetShadingRateSampleLocationivNV);
  pfn_glGetShadingRateSampleLocationivNV(rate,samples,index,location);
}
GLAPI void APIENTRY glShadingRateImageBarrierNV(GLboolean synchronize)
{
  assert(pfn_glShadingRateImageBarrierNV);
  pfn_glShadingRateImageBarrierNV(synchronize);
}
GLAPI void APIENTRY glShadingRateImagePaletteNV(GLuint viewport, GLuint first, GLsizei count, const GLenum* rates)
{
  assert(pfn_glShadingRateImagePaletteNV);
  pfn_glShadingRateImagePaletteNV(viewport,first,count,rates);
}
GLAPI void APIENTRY glShadingRateSampleOrderNV(GLenum order)
{
  assert(pfn_glShadingRateSampleOrderNV);
  pfn_glShadingRateSampleOrderNV(order);
}
GLAPI void APIENTRY glShadingRateSampleOrderCustomNV(GLenum rate, GLuint samples, const GLint* locations)
{
  assert(pfn_glShadingRateSampleOrderCustomNV);
  pfn_glShadingRateSampleOrderCustomNV(rate,samples,locations);
}

int load_GL_NV_shading_rate_image(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glBindShadingRateImageNV = (PFNGLBINDSHADINGRATEIMAGENVPROC)fnGetProcAddress("glBindShadingRateImageNV");
  pfn_glGetShadingRateImagePaletteNV = (PFNGLGETSHADINGRATEIMAGEPALETTENVPROC)fnGetProcAddress("glGetShadingRateImagePaletteNV");
  pfn_glGetShadingRateSampleLocationivNV = (PFNGLGETSHADINGRATESAMPLELOCATIONIVNVPROC)fnGetProcAddress("glGetShadingRateSampleLocationivNV");
  pfn_glShadingRateImageBarrierNV = (PFNGLSHADINGRATEIMAGEBARRIERNVPROC)fnGetProcAddress("glShadingRateImageBarrierNV");
  pfn_glShadingRateImagePaletteNV = (PFNGLSHADINGRATEIMAGEPALETTENVPROC)fnGetProcAddress("glShadingRateImagePaletteNV");
  pfn_glShadingRateSampleOrderNV = (PFNGLSHADINGRATESAMPLEORDERNVPROC)fnGetProcAddress("glShadingRateSampleOrderNV");
  pfn_glShadingRateSampleOrderCustomNV = (PFNGLSHADINGRATESAMPLEORDERCUSTOMNVPROC)fnGetProcAddress("glShadingRateSampleOrderCustomNV");
  int success = has_extension("GL_NV_shading_rate_image");
  success = success && (pfn_glBindShadingRateImageNV != 0);
  success = success && (pfn_glGetShadingRateImagePaletteNV != 0);
  success = success && (pfn_glGetShadingRateSampleLocationivNV != 0);
  success = success && (pfn_glShadingRateImageBarrierNV != 0);
  success = success && (pfn_glShadingRateImagePaletteNV != 0);
  success = success && (pfn_glShadingRateSampleOrderNV != 0);
  success = success && (pfn_glShadingRateSampleOrderCustomNV != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_stereo_view_rendering */



int load_GL_NV_stereo_view_rendering(nvGLLoaderGetProcFN fnGetProcAddress)
{
  int success = has_extension("GL_NV_stereo_view_rendering");
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_texture_multisample */

static PFNGLTEXIMAGE2DMULTISAMPLECOVERAGENVPROC pfn_glTexImage2DMultisampleCoverageNV = 0;
static PFNGLTEXIMAGE3DMULTISAMPLECOVERAGENVPROC pfn_glTexImage3DMultisampleCoverageNV = 0;
static PFNGLTEXTUREIMAGE2DMULTISAMPLENVPROC pfn_glTextureImage2DMultisampleNV = 0;
static PFNGLTEXTUREIMAGE3DMULTISAMPLENVPROC pfn_glTextureImage3DMultisampleNV = 0;
static PFNGLTEXTUREIMAGE2DMULTISAMPLECOVERAGENVPROC pfn_glTextureImage2DMultisampleCoverageNV = 0;
static PFNGLTEXTUREIMAGE3DMULTISAMPLECOVERAGENVPROC pfn_glTextureImage3DMultisampleCoverageNV = 0;

GLAPI void APIENTRY glTexImage2DMultisampleCoverageNV(GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations)
{
  assert(pfn_glTexImage2DMultisampleCoverageNV);
  pfn_glTexImage2DMultisampleCoverageNV(target,coverageSamples,colorSamples,internalFormat,width,height,fixedSampleLocations);
}
GLAPI void APIENTRY glTexImage3DMultisampleCoverageNV(GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations)
{
  assert(pfn_glTexImage3DMultisampleCoverageNV);
  pfn_glTexImage3DMultisampleCoverageNV(target,coverageSamples,colorSamples,internalFormat,width,height,depth,fixedSampleLocations);
}
GLAPI void APIENTRY glTextureImage2DMultisampleNV(GLuint texture, GLenum target, GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations)
{
  assert(pfn_glTextureImage2DMultisampleNV);
  pfn_glTextureImage2DMultisampleNV(texture,target,samples,internalFormat,width,height,fixedSampleLocations);
}
GLAPI void APIENTRY glTextureImage3DMultisampleNV(GLuint texture, GLenum target, GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations)
{
  assert(pfn_glTextureImage3DMultisampleNV);
  pfn_glTextureImage3DMultisampleNV(texture,target,samples,internalFormat,width,height,depth,fixedSampleLocations);
}
GLAPI void APIENTRY glTextureImage2DMultisampleCoverageNV(GLuint texture, GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations)
{
  assert(pfn_glTextureImage2DMultisampleCoverageNV);
  pfn_glTextureImage2DMultisampleCoverageNV(texture,target,coverageSamples,colorSamples,internalFormat,width,height,fixedSampleLocations);
}
GLAPI void APIENTRY glTextureImage3DMultisampleCoverageNV(GLuint texture, GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations)
{
  assert(pfn_glTextureImage3DMultisampleCoverageNV);
  pfn_glTextureImage3DMultisampleCoverageNV(texture,target,coverageSamples,colorSamples,internalFormat,width,height,depth,fixedSampleLocations);
}

int load_GL_NV_texture_multisample(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glTexImage2DMultisampleCoverageNV = (PFNGLTEXIMAGE2DMULTISAMPLECOVERAGENVPROC)fnGetProcAddress("glTexImage2DMultisampleCoverageNV");
  pfn_glTexImage3DMultisampleCoverageNV = (PFNGLTEXIMAGE3DMULTISAMPLECOVERAGENVPROC)fnGetProcAddress("glTexImage3DMultisampleCoverageNV");
  pfn_glTextureImage2DMultisampleNV = (PFNGLTEXTUREIMAGE2DMULTISAMPLENVPROC)fnGetProcAddress("glTextureImage2DMultisampleNV");
  pfn_glTextureImage3DMultisampleNV = (PFNGLTEXTUREIMAGE3DMULTISAMPLENVPROC)fnGetProcAddress("glTextureImage3DMultisampleNV");
  pfn_glTextureImage2DMultisampleCoverageNV = (PFNGLTEXTUREIMAGE2DMULTISAMPLECOVERAGENVPROC)fnGetProcAddress("glTextureImage2DMultisampleCoverageNV");
  pfn_glTextureImage3DMultisampleCoverageNV = (PFNGLTEXTUREIMAGE3DMULTISAMPLECOVERAGENVPROC)fnGetProcAddress("glTextureImage3DMultisampleCoverageNV");
  int success = has_extension("GL_NV_texture_multisample");
  success = success && (pfn_glTexImage2DMultisampleCoverageNV != 0);
  success = success && (pfn_glTexImage3DMultisampleCoverageNV != 0);
  success = success && (pfn_glTextureImage2DMultisampleNV != 0);
  success = success && (pfn_glTextureImage3DMultisampleNV != 0);
  success = success && (pfn_glTextureImage2DMultisampleCoverageNV != 0);
  success = success && (pfn_glTextureImage3DMultisampleCoverageNV != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_uniform_buffer_unified_memory */



int load_GL_NV_uniform_buffer_unified_memory(nvGLLoaderGetProcFN fnGetProcAddress)
{
  int success = has_extension("GL_NV_uniform_buffer_unified_memory");
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_vertex_buffer_unified_memory */

static PFNGLBUFFERADDRESSRANGENVPROC pfn_glBufferAddressRangeNV = 0;
static PFNGLVERTEXFORMATNVPROC pfn_glVertexFormatNV = 0;
static PFNGLNORMALFORMATNVPROC pfn_glNormalFormatNV = 0;
static PFNGLCOLORFORMATNVPROC pfn_glColorFormatNV = 0;
static PFNGLINDEXFORMATNVPROC pfn_glIndexFormatNV = 0;
static PFNGLTEXCOORDFORMATNVPROC pfn_glTexCoordFormatNV = 0;
static PFNGLEDGEFLAGFORMATNVPROC pfn_glEdgeFlagFormatNV = 0;
static PFNGLSECONDARYCOLORFORMATNVPROC pfn_glSecondaryColorFormatNV = 0;
static PFNGLFOGCOORDFORMATNVPROC pfn_glFogCoordFormatNV = 0;
static PFNGLVERTEXATTRIBFORMATNVPROC pfn_glVertexAttribFormatNV = 0;
static PFNGLVERTEXATTRIBIFORMATNVPROC pfn_glVertexAttribIFormatNV = 0;
static PFNGLGETINTEGERUI64I_VNVPROC pfn_glGetIntegerui64i_vNV = 0;

GLAPI void APIENTRY glBufferAddressRangeNV(GLenum pname, GLuint index, GLuint64EXT address, GLsizeiptr length)
{
  assert(pfn_glBufferAddressRangeNV);
  pfn_glBufferAddressRangeNV(pname,index,address,length);
}
GLAPI void APIENTRY glVertexFormatNV(GLint size, GLenum type, GLsizei stride)
{
  assert(pfn_glVertexFormatNV);
  pfn_glVertexFormatNV(size,type,stride);
}
GLAPI void APIENTRY glNormalFormatNV(GLenum type, GLsizei stride)
{
  assert(pfn_glNormalFormatNV);
  pfn_glNormalFormatNV(type,stride);
}
GLAPI void APIENTRY glColorFormatNV(GLint size, GLenum type, GLsizei stride)
{
  assert(pfn_glColorFormatNV);
  pfn_glColorFormatNV(size,type,stride);
}
GLAPI void APIENTRY glIndexFormatNV(GLenum type, GLsizei stride)
{
  assert(pfn_glIndexFormatNV);
  pfn_glIndexFormatNV(type,stride);
}
GLAPI void APIENTRY glTexCoordFormatNV(GLint size, GLenum type, GLsizei stride)
{
  assert(pfn_glTexCoordFormatNV);
  pfn_glTexCoordFormatNV(size,type,stride);
}
GLAPI void APIENTRY glEdgeFlagFormatNV(GLsizei stride)
{
  assert(pfn_glEdgeFlagFormatNV);
  pfn_glEdgeFlagFormatNV(stride);
}
GLAPI void APIENTRY glSecondaryColorFormatNV(GLint size, GLenum type, GLsizei stride)
{
  assert(pfn_glSecondaryColorFormatNV);
  pfn_glSecondaryColorFormatNV(size,type,stride);
}
GLAPI void APIENTRY glFogCoordFormatNV(GLenum type, GLsizei stride)
{
  assert(pfn_glFogCoordFormatNV);
  pfn_glFogCoordFormatNV(type,stride);
}
GLAPI void APIENTRY glVertexAttribFormatNV(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride)
{
  assert(pfn_glVertexAttribFormatNV);
  pfn_glVertexAttribFormatNV(index,size,type,normalized,stride);
}
GLAPI void APIENTRY glVertexAttribIFormatNV(GLuint index, GLint size, GLenum type, GLsizei stride)
{
  assert(pfn_glVertexAttribIFormatNV);
  pfn_glVertexAttribIFormatNV(index,size,type,stride);
}
GLAPI void APIENTRY glGetIntegerui64i_vNV(GLenum value, GLuint index, GLuint64EXT* result)
{
  assert(pfn_glGetIntegerui64i_vNV);
  pfn_glGetIntegerui64i_vNV(value,index,result);
}

int load_GL_NV_vertex_buffer_unified_memory(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glBufferAddressRangeNV = (PFNGLBUFFERADDRESSRANGENVPROC)fnGetProcAddress("glBufferAddressRangeNV");
  pfn_glVertexFormatNV = (PFNGLVERTEXFORMATNVPROC)fnGetProcAddress("glVertexFormatNV");
  pfn_glNormalFormatNV = (PFNGLNORMALFORMATNVPROC)fnGetProcAddress("glNormalFormatNV");
  pfn_glColorFormatNV = (PFNGLCOLORFORMATNVPROC)fnGetProcAddress("glColorFormatNV");
  pfn_glIndexFormatNV = (PFNGLINDEXFORMATNVPROC)fnGetProcAddress("glIndexFormatNV");
  pfn_glTexCoordFormatNV = (PFNGLTEXCOORDFORMATNVPROC)fnGetProcAddress("glTexCoordFormatNV");
  pfn_glEdgeFlagFormatNV = (PFNGLEDGEFLAGFORMATNVPROC)fnGetProcAddress("glEdgeFlagFormatNV");
  pfn_glSecondaryColorFormatNV = (PFNGLSECONDARYCOLORFORMATNVPROC)fnGetProcAddress("glSecondaryColorFormatNV");
  pfn_glFogCoordFormatNV = (PFNGLFOGCOORDFORMATNVPROC)fnGetProcAddress("glFogCoordFormatNV");
  pfn_glVertexAttribFormatNV = (PFNGLVERTEXATTRIBFORMATNVPROC)fnGetProcAddress("glVertexAttribFormatNV");
  pfn_glVertexAttribIFormatNV = (PFNGLVERTEXATTRIBIFORMATNVPROC)fnGetProcAddress("glVertexAttribIFormatNV");
  pfn_glGetIntegerui64i_vNV = (PFNGLGETINTEGERUI64I_VNVPROC)fnGetProcAddress("glGetIntegerui64i_vNV");
  int success = has_extension("GL_NV_vertex_buffer_unified_memory");
  success = success && (pfn_glBufferAddressRangeNV != 0);
  success = success && (pfn_glVertexFormatNV != 0);
  success = success && (pfn_glNormalFormatNV != 0);
  success = success && (pfn_glColorFormatNV != 0);
  success = success && (pfn_glIndexFormatNV != 0);
  success = success && (pfn_glTexCoordFormatNV != 0);
  success = success && (pfn_glEdgeFlagFormatNV != 0);
  success = success && (pfn_glSecondaryColorFormatNV != 0);
  success = success && (pfn_glFogCoordFormatNV != 0);
  success = success && (pfn_glVertexAttribFormatNV != 0);
  success = success && (pfn_glVertexAttribIFormatNV != 0);
  success = success && (pfn_glGetIntegerui64i_vNV != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_viewport_swizzle */

static PFNGLVIEWPORTSWIZZLENVPROC pfn_glViewportSwizzleNV = 0;

GLAPI void APIENTRY glViewportSwizzleNV(GLuint index, GLenum swizzlex, GLenum swizzley, GLenum swizzlez, GLenum swizzlew)
{
  assert(pfn_glViewportSwizzleNV);
  pfn_glViewportSwizzleNV(index,swizzlex,swizzley,swizzlez,swizzlew);
}

int load_GL_NV_viewport_swizzle(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glViewportSwizzleNV = (PFNGLVIEWPORTSWIZZLENVPROC)fnGetProcAddress("glViewportSwizzleNV");
  int success = has_extension("GL_NV_viewport_swizzle");
  success = success && (pfn_glViewportSwizzleNV != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_NVX_gpu_memory_info */



int load_GL_NVX_gpu_memory_info(nvGLLoaderGetProcFN fnGetProcAddress)
{
  int success = has_extension("GL_NVX_gpu_memory_info");
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_query_resource */

static PFNGLQUERYRESOURCENVPROC pfn_glQueryResourceNV = 0;

GLAPI GLint APIENTRY glQueryResourceNV(GLenum queryType, GLint tagId, GLuint bufSize, GLint* buffer)
{
  assert(pfn_glQueryResourceNV);
  return pfn_glQueryResourceNV(queryType,tagId,bufSize,buffer);
}

int load_GL_NV_query_resource(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glQueryResourceNV = (PFNGLQUERYRESOURCENVPROC)fnGetProcAddress("glQueryResourceNV");
  int success = has_extension("GL_NV_query_resource");
  success = success && (pfn_glQueryResourceNV != 0);
  return success;
}

/* /////////////////////////////////// */
/* GL_NV_query_resource_tag */

static PFNGLGENQUERYRESOURCETAGNVPROC pfn_glGenQueryResourceTagNV = 0;
static PFNGLDELETEQUERYRESOURCETAGNVPROC pfn_glDeleteQueryResourceTagNV = 0;
static PFNGLQUERYRESOURCETAGNVPROC pfn_glQueryResourceTagNV = 0;

GLAPI void APIENTRY glGenQueryResourceTagNV(GLsizei n, GLint* tagIds)
{
  assert(pfn_glGenQueryResourceTagNV);
  pfn_glGenQueryResourceTagNV(n,tagIds);
}
GLAPI void APIENTRY glDeleteQueryResourceTagNV(GLsizei n, const GLint* tagIds)
{
  assert(pfn_glDeleteQueryResourceTagNV);
  pfn_glDeleteQueryResourceTagNV(n,tagIds);
}
GLAPI void APIENTRY glQueryResourceTagNV(GLint tagId, const GLchar* tagString)
{
  assert(pfn_glQueryResourceTagNV);
  pfn_glQueryResourceTagNV(tagId,tagString);
}

int load_GL_NV_query_resource_tag(nvGLLoaderGetProcFN fnGetProcAddress)
{
  pfn_glGenQueryResourceTagNV = (PFNGLGENQUERYRESOURCETAGNVPROC)fnGetProcAddress("glGenQueryResourceTagNV");
  pfn_glDeleteQueryResourceTagNV = (PFNGLDELETEQUERYRESOURCETAGNVPROC)fnGetProcAddress("glDeleteQueryResourceTagNV");
  pfn_glQueryResourceTagNV = (PFNGLQUERYRESOURCETAGNVPROC)fnGetProcAddress("glQueryResourceTagNV");
  int success = has_extension("GL_NV_query_resource_tag");
  success = success && (pfn_glGenQueryResourceTagNV != 0);
  success = success && (pfn_glDeleteQueryResourceTagNV != 0);
  success = success && (pfn_glQueryResourceTagNV != 0);
  return success;
}


