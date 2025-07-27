# main.py

import argparse
import subprocess
import sys

def parse_args():
    p = argparse.ArgumentParser(
        description="Orchestrate your full pipeline"
    )
    p.add_argument(
        "--mode", choices=["train", "test", "all"],
        default="all",
        help="What to run: train, test, or both"
    )
    return p.parse_args()

def main():
    args = parse_args()

    if args.mode in ("train", "all"):
        print("▶ Running train.py …")
        res = subprocess.run([sys.executable, "train.py"])
        if res.returncode != 0:
            print("‼ train.py failed", file=sys.stderr)
            sys.exit(res.returncode)

    if args.mode in ("test", "all"):
        print("▶ Running test.py …")
        res = subprocess.run([sys.executable, "test.py"])
        if res.returncode != 0:
            print("‼ test.py failed", file=sys.stderr)
            sys.exit(res.returncode)

if __name__ == "__main__":
    main()
