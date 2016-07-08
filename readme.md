## Cross Process GLX

This is a simple demo app to test out using GLX across process on X11.

To run it, use `make`, run `./host`, copy the window id, run `./client`, and paste the window id, and it *should* work.

Note: there is no attempt at cleaning up the resources here, everything leaks. This is just a demo.
