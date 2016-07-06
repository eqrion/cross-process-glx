#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/utsname.h>

#include <GL/gl.h>
#include <GL/glx.h>

// Initialization

static Window create_window(Display *display, unsigned int width, unsigned int height)
{
  int attrib[] = { GLX_RGBA,
      GLX_RED_SIZE, 1,
      GLX_GREEN_SIZE, 1,
      GLX_BLUE_SIZE, 1,
      GLX_DOUBLEBUFFER,
      None
  };

  int screen = DefaultScreen(display);
  Window root = RootWindow(display, screen);

  XVisualInfo *visualinfo = glXChooseVisual(display, screen, attrib);
  if (!visualinfo)
  {
    printf("error, couldn't get the correct buffer.\n");
    exit(1);
  }

  XSetWindowAttributes attr = {0};
  attr.background_pixel = 0;
  attr.border_pixel = 0;
  attr.colormap = XCreateColormap(display, root, visualinfo->visual, AllocNone);
  attr.event_mask = StructureNotifyMask | ExposureMask;

  unsigned long mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

  Window window = XCreateWindow(
      display,
      root,
      0,
      0,
      width,
      height,
      0,
      visualinfo->depth,
      InputOutput,
      visualinfo->visual,
      mask,
      &attr);

  XMapWindow(display, window);

  return window;
}

// Event Loop

static void event_loop(Display *display, Window window)
{
  XEvent event;

  while (1)
  {
    XNextEvent(display, &event);
    printf("event: %d\n", event.type);
  }
}

// Main

int main(int argc, char* argv[])
{
  Display *display = XOpenDisplay(NULL);

  Window window = create_window(display, 400, 400);
  printf("window = %u\n", window);

  event_loop(display, window);

  return 0;
}
