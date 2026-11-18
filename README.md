# cube
A text-based input 3d polyhedra renderer. Although the name of the project was a joke on how it was the only thing it could render, it can render any mesh of verteces and edges.

## how to cube
Notice that, to use **cube**, you will need to install **raylib**, as we use this to render things on a window.

If running on Linux, it is highly advised to create a symlink to the program to run easily on the terminal. 
```bash
sudo ln -s /path/to/cube /usr/local/bin/cube
```

The program can admit one singular input file, which contains both the verteces and edges of the mesh to render. If no input file is provided, **cube** will render a cube.

```bash
cube samples/cube.txt
```

A directory with sample meshes is provided in the repository, available to render out-of-the-box. The input file must be structured in a way so that it provides the following items in order:

1. The number of verteces
2. The verteces of the mesh, centered at $(0, 0, 0)$.
3. The number of edges
4. The edges of the mesh

The verteces must be provided by their spatial coordinates, with $z$ going upwards, separated by spaces. The edges must be provided by the verteces it connects. This will be done with the **vertex index**, which is set in input order starting at 0.

Any lines after the input will be treated as comments, as they won't be read by the program. An example is provided below.

```text
8
1 1 -1
1 -1 -1
-1 -1 -1
-1 1 -1
1 1 1
1 -1 1
-1 -1 1
-1 1 1

12
0 1
0 3
0 4
1 2
1 5
2 3
2 6
3 7
4 5
4 7
5 6
6 7

The following lines are treated as comments.
This file will input a cube.
```

## when to cube
You can **cube** whenever you want! When bored, to kill time, when taking a *very long and boring class* or when in court, it's always a good time to **cube**!

## what to cube
You can **cube** any polyhedra, as long as you can denote it as a set of **up to 256 verteces** and **up to 512 edges**. Going over these limits does not guarantee your cubing.
