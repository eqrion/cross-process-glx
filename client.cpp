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

static void attach_window(Display *display, Window window)
{
  XSelectInput(display, window, StructureNotifyMask | ExposureMask);
}
static void create_gl(Display *display, Window window)
{
  int screen = DefaultScreen(display);
	int attrib[] = { GLX_RGBA,
		  GLX_RED_SIZE, 1,
		  GLX_GREEN_SIZE, 1,
		  GLX_BLUE_SIZE, 1,
		  GLX_DOUBLEBUFFER,
		  None };

  XVisualInfo *visualinfo = glXChooseVisual(display, screen, attrib);
  if (!visualinfo)
  {
    printf("error, couldn't get the correct buffer.\n");
    exit(1);
  }

  GLXContext context = glXCreateContext(display, visualinfo, NULL, True);
	if (!context)
  {
    printf("error, couldn't create a context.\n");
		exit(1);
	}

	glXMakeCurrent(display, window, context);

  glShadeModel(GL_FLAT);
  glClearColor(0.5, 0.5, 0.5, 1.0);
}

// Event Loop

static void redraw(Display *display, Window window)
{
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(1.0, 1.0, 0.0);
  glRectf(-0.8, -0.8, 0.8, 0.8);

  glXSwapBuffers(display, window);
}

static void resize(unsigned int width, unsigned int height)
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

static void event_loop(Display *display, Window window)
{
  redraw(display, window);

	XEvent event;

	while (1)
  {
		XNextEvent(display, &event);
		printf("event: %d\n", event.type);

		switch (event.type)
    {
      case Expose:
      {
        redraw(display, event.xany.window);
      }
		  break;

		  case ConfigureNotify:
      {
        resize(event.xconfigure.width, event.xconfigure.height);
      }
		  break;
		}
	}
}

// Main

int main(int argc, char* argv[])
{
	Display *display = XOpenDisplay(NULL);

	Window window = 0;
  printf("window = ");
	if (scanf("%u", &window) != 1)
  {
		printf("error, couldn't read window id.\n");
		exit(1);
	}

  attach_window(display, window);
	create_gl(display, window);

	event_loop(display, window);

	return 0;
}
