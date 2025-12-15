#!/usr/bin/env bash
# Runner script for parser tests

set -u  # keep unset-variable protection
# DO NOT use -e or pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
TEST_DIR="$ROOT_DIR/tests/parser_tests"
RESULT_LOG="$TEST_DIR/results.log"

echo "Building project (if Makefile present)..."
if [ -f "$ROOT_DIR/Makefile" ]; then
  (cd "$ROOT_DIR" && make) || {
    echo "make failed; please build the project manually and ensure the binary is named './miniRT'" >&2
  }
fi

BIN="$ROOT_DIR/miniRT"
if [ ! -x "$BIN" ]; then
  echo "Warning: binary '$BIN' not found or not executable." >&2
fi

echo "Running parser tests from $TEST_DIR"
echo "Test run started at $(date)" > "$RESULT_LOG"

for f in "$TEST_DIR"/*.rt; do
  echo "--- Test: $f ---" | tee -a "$RESULT_LOG"
  if [ -x "$BIN" ]; then
    printf "Command: %s %s\n" "$BIN" "$f" | tee -a "$RESULT_LOG"

    # run test, capture output + exit code safely
    output="$("$BIN" "$f" 2>&1)"
    rc=$?

    printf "%s\n" "$output" | sed 's/^/    /' | tee -a "$RESULT_LOG"
    echo "Exit code: $rc" | tee -a "$RESULT_LOG"
  else
    echo "Binary not available; cannot run test" | tee -a "$RESULT_LOG"
  fi
  echo "" | tee -a "$RESULT_LOG"
done

echo "Test run complete. Results saved to $RESULT_LOG"
