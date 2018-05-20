LinkerSettings = -lGL -lGLU -lglut -lm
DebugSetting = -ggdb

all: main tests

main: clab_assignment_graphics

tests: tests/glWindowANDglDrawFuncsTest tests/stickmanTest tests/bitmapTest tests/lineCircleIntersectTest
	

%.o: %.c %.h
	gcc -c -o $@ $< ${DebugSetting}

clab_assignment_graphics: clab_assignment_graphics.o ogl_gui/glwindow.o ogl_gui/glDrawFuncs.o ogl_gui/bitmaps.o ogl_gui/bitmapFonts.o ogl_gui/vector3.o ogl_gui/colours.o ogl_gui/buttons.o stickman/stickman.o utils/keys.o physics/physics.o physics/collisions.o physics/world.o physics/objects.o simLevels.o ogl_gui/errors.o 
	gcc -o $@ $^ ${LinkerSettings}

tests/glWindowANDglDrawFuncsTest: tests/glWindowANDglDrawFuncsTest.o ogl_gui/glwindow.o ogl_gui/glDrawFuncs.o ogl_gui/vector3.o ogl_gui/colours.o
	gcc -o $@ $^ ${LinkerSettings}

tests/lineCircleIntersectTest: tests/lineCircleIntersectTest.o ogl_gui/glwindow.o ogl_gui/glDrawFuncs.o ogl_gui/vector3.o ogl_gui/colours.o physics/collisions.o physics/objects.o
	gcc -o $@ $^ ${LinkerSettings}

tests/stickmanTest: tests/stickmanTest.o ogl_gui/glwindow.o ogl_gui/glDrawFuncs.o stickman/stickman.o ogl_gui/vector3.o ogl_gui/colours.o
	gcc -o $@ $^ ${LinkerSettings}
	
tests/bitmapTest: tests/bitmapTest.o ogl_gui/bitmaps.o ogl_gui/bitmapFonts.o ogl_gui/glwindow.o ogl_gui/glDrawFuncs.o ogl_gui/errors.o
	gcc -o $@ $^ ${LinkerSettings}


.PHONY: clean
clean: 
	rm -f clab_assignment_graphics
	rm -f clab_assignment_graphics.o
	rm -f simLevels.o
	rm -f levels.o
	rm -f stickman/stickman.o
	rm -f utils/keys.o
	rm -f physics/physics.o
	rm -f physics/world.o
	rm -f physics/objects.o
	rm -f physics/collisions.o
	rm -f ogl_gui/glwindow.o
	rm -f ogl_gui/glDrawFuncs.o
	rm -f ogl_gui/colours.o
	rm -f ogl_gui/vector3.o
	rm -f ogl_gui/errors.o
	rm -f ogl_gui/bitmaps.o
	rm -f ogl_gui/bitmapFonts.o
	rm -f ogl_gui/buttons.o	
	rm -f tests/stickmanTest.o
	rm -f tests/glWindowANDglDrawFuncsTest.o
	rm -f tests/bitmapTest.o
	rm -f tests/levelEditor.o
	rm -f tests/lineCircleIntersectTest.o
	rm -f tests/stickmanTest
	rm -f tests/glWindowANDglDrawFuncsTest
	rm -f tests/bitmapTest
	rm -f tests/levelEditor
	rm -f tests/lineCircleIntersectTest
