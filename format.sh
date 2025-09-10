#!/usr/bin/env bash
set -eo pipefail

src_dirs="src test"
find $src_dirs -type f \( -iname '*.c' -o -iname '*.h' -o -iname '*.cpp' -o -iname '*.hpp' \) | while read -r f; do
  echo "formatting $f"
  clang-format -i "$f"
done