#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

MAP_GLOB="${1:-maps/maps??.cub}"
IMAGE_NAME="${CUB3D_DOCKER_IMAGE:-cub3d-build}"
case "$(uname -s)" in
  Darwin) DEFAULT_DISPLAY="host.docker.internal:0" ;;
  *) DEFAULT_DISPLAY="${DISPLAY:-:0}" ;;
esac
DISPLAY_VALUE="${CUB3D_DISPLAY:-$DEFAULT_DISPLAY}"

ensure_image() {
  if ! docker image inspect "$IMAGE_NAME" >/dev/null 2>&1; then
    echo "Docker image '$IMAGE_NAME' not found. Building it from ./Dockerfile..."
    docker build -t "$IMAGE_NAME" .
  fi
}

list_maps() {
  find maps -maxdepth 1 -type f -name "$(basename "$MAP_GLOB")" | sort
}

run_map() {
  local map_file="$1"
  docker run --rm -it \
    -e DISPLAY="$DISPLAY_VALUE" \
    -e MAP_FILE="$map_file" \
    -v "$SCRIPT_DIR":/work -w /work \
    "$IMAGE_NAME" \
    bash -lc 'make >/dev/null && ./cub3D "$MAP_FILE"'
}

MAPS=()
while IFS= read -r line; do
  MAPS+=("$line")
done < <(list_maps)

if [ ${#MAPS[@]} -eq 0 ]; then
  echo "No map found for pattern: $MAP_GLOB"
  exit 1
fi

ensure_image

echo "${#MAPS[@]} map(s) found."
echo "Pattern: $MAP_GLOB"
echo "Docker image: $IMAGE_NAME"
echo "DISPLAY: $DISPLAY_VALUE"
echo

for map in "${MAPS[@]}"; do
  echo "========================================"
  echo "Prochaine map: $map"
  read -r -p "Entree = lancer | q = quitter : " ans
  if [[ "${ans:-}" =~ ^[Qq]$ ]]; then
    echo "Stop requested."
    exit 0
  fi
  run_map "$map"
  echo
  echo "Done: $map"
done

echo "All maps were tested."
