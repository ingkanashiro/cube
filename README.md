# cube
A text-based input 3d polyhedra renderer. Although the name of the project was a joke on how it was the only thing it could render, it can render any mesh of verteces and edges.

## get started
Notice that, to use **cube**, you will need to install **raylib**, as we use this to render things on a window.

If running on Linux, it is highly advised to create a symlink to the program to run easily on the terminal. 
```bash
sudo ln -s /path/to/cube /usr/local/bin/cube
```

> [!WARNING]
> If running on Windows, you can achieve the same effect by adding the program to the PATH. Notice that **no official binary release is available at the moment, so you will need to compile the program yourself**.

The program can admit one singular input file, which contains both the verteces and edges of the mesh to render. If no input file is provided, **cube** will render a cube.

```bash
cube samples/cube.txt
```

## how to cube
In order to **cube**, you only need to run the program. However, you can add various flags, which are modifiers that change the behaviour of the **cube** process in various ways.

> [!IMPORTANT]
> - **Mesh:** Specified with flag `-m`. Provides an input file for the mesh displayed. A mesh input format is appended below. Multiple meshes can be provided if paths to each mesh are separated by commas. 
> - **Speed:** Specified with flag `-s`. Changes the speed of rotation of the shape. *(Default: 1.0)*
> - **Acceleration:** Specified with flag `-a`. Changes the spin acceleration of the shape. *(Default: 0.0)*
> - **Phase:** Specificed with flag `-p`. Determines the starting position, given in fractions of a full rotation. *(Default: 0.0)* 
> - **Zoom level:** Specified with flag `-z`. Determines the scale factor of the shape. *(Default: 1.0)*
> - **Window size:** Specified with flag `-w`. Determines the side lenght of the window. *(Default: 480)*
> - **Color:** Specified with flag `-c`. Determines color of each mesh, separated by commas. A color guide is appended below. *(Default: 0)*

All the flags are optional, but the program will require that flags appear in pairs, that is, for every flag `-x`, you need to include a value field `<value>` immediately after.

> [!TIP]
> A directory with sample meshes is provided in the repository, available to render out-of-the-box. The input file must be structured in a way so that it provides the following items in order:
> 
> 1. The number of verteces
> 2. The verteces of the mesh, centered at $(0, 0, 0)$.
> 3. The number of edges
> 4. The edges of the mesh
> 
> The verteces must be provided by their spatial coordinates, with $z$ going upwards, separated by spaces. The edges must be provided by the verteces it connects. This will be done with the **vertex index**, which is set in input order starting at 0.
> 
> Any lines after the input will be treated as comments, as they won't be read by the program. An example is provided below.
> 
> ```text
> 8
> 1 1 -1
> 1 -1 -1
> -1 -1 -1
> -1 1 -1
> 1 1 1
> 1 -1 1
> -1 -1 1
> -1 1 1
> 
> 12
> 0 1
> 0 3
> 0 4
> 1 2
> 1 5
> 2 3
> 2 6
> 3 7
> 4 5
> 4 7
> 5 6
> 6 7
> 
> The following lines are treated as comments.
> This file will input a cube.
> ```

## when to cube
You can **cube** whenever you want! When bored, to kill time, when taking a *very long and boring class* or when in court, it's always a good time to **cube**!

## what to cube
You can **cube** any polyhedra, as long as you can denote it as a set of **up to 256 verteces** and **up to 512 edges**. Going over these limits does not guarantee your cubing.
