#!/usr/bin/env bash
set -euo pipefail

MAP_GLOB="${1:-maps/maps??.cub}"

MAPS=()
while IFS= read -r line; do
  MAPS+=("$line")
done < <(ls $MAP_GLOB 2>/dev/null | sort)

if [ ${#MAPS[@]} -eq 0 ]; then
  echo "No map found for pattern: $MAP_GLOB"
  exit 1
fi

echo "${#MAPS[@]} map(s) found."
echo "Pattern: $MAP_GLOB"
echo

for map in "${MAPS[@]}"; do
  echo "========================================"
  echo "Prochaine map: $map"
  read -r -p "Entrée = lancer | q = quitter : " ans
  if [[ "${ans:-}" =~ ^[Qq]$ ]]; then
    echo "Stop requested."
    exit 0
  fi

  docker run --rm -it \
    -e DISPLAY=host.docker.internal:0 \
    -e MAP_FILE="$map" \
    -v "$PWD":/work -w /work \
    cub3d-build \
    bash -lc 'make >/dev/null && ./cub3D "$MAP_FILE"'

  echo
  echo "Done: $map"
done

echo "All maps were tested."
