/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

/** \file
 * \ingroup GHOST
 */

#ifndef __GHOST_IXRGRAPHICSBINDING_H__
#define __GHOST_IXRGRAPHICSBINDING_H__

#include <memory>
#include <vector>
#include "GHOST_Xr_openxr_includes.h"

class GHOST_IXrGraphicsBinding {
  friend std::unique_ptr<GHOST_IXrGraphicsBinding> GHOST_XrGraphicsBindingCreateFromType(
      GHOST_TXrGraphicsBinding type);

 public:
  union {
#if defined(WITH_X11)
    XrGraphicsBindingOpenGLXlibKHR glx;
#elif defined(WIN32)
    XrGraphicsBindingOpenGLWin32KHR wgl;
    XrGraphicsBindingD3D11KHR d3d11;
#endif
  } oxr_binding;

  virtual void initFromGhostContext(class GHOST_Context *ghost_ctx) = 0;
  virtual bool chooseSwapchainFormat(const std::vector<int64_t> &runtime_formats,
                                     int64_t *r_result) const = 0;
  virtual std::vector<XrSwapchainImageBaseHeader *> createSwapchainImages(
      uint32_t image_count) = 0;
  virtual void drawViewBegin(XrSwapchainImageBaseHeader *swapchain_image) = 0;
  virtual void drawViewEnd(XrSwapchainImageBaseHeader *swapchain_image) = 0;

 protected:
  /* Use GHOST_XrGraphicsBindingCreateFromType */
  GHOST_IXrGraphicsBinding() = default;
};

std::unique_ptr<GHOST_IXrGraphicsBinding> GHOST_XrGraphicsBindingCreateFromType(
    GHOST_TXrGraphicsBinding type);

#endif /* __GHOST_IXRGRAPHICSBINDING_H__ */
