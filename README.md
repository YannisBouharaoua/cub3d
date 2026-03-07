*This project has been created as part of the 42 curriculum by yabouhar, mmestron.*

# cub3D

## Description

`cub3D` is a raycasting project inspired by Wolfenstein 3D. The program renders a
first-person view of a maze described in a `.cub` file, using `miniLibX`.

The current repository stores the project sources in `cub3d/`.

## Instructions

Build on Linux:

```bash
cd cub3d
make
./cub3D maps/maps05.cub
```

Build and run with the provided Docker image:

```bash
cd cub3d
docker build -t cub3d-build .
docker run --rm -it \
  -e DISPLAY=host.docker.internal:0 \
  -v "$PWD":/work -w /work \
  cub3d-build \
  bash -lc 'make && ./cub3D maps/maps05.cub'
```

Test multiple maps with the helper script:

```bash
cd cub3d
./all_maps.sh
```

## Resources

- 42 cub3D subject
- miniLibX documentation: `cub3d/minilibx-linux/README.md`
- Lode Vandevenne raycasting tutorial: <https://lodev.org/cgtutor/raycasting.html>
- Permadi raycasting articles: <https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/>

AI usage:

- analysis of the existing parser and map validation logic
- identification of mismatches with the 42 subject and the Norm
- assistance for refactoring the parser, cleanup paths, and leak prevention

