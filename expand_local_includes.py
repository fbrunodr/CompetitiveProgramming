import sys
from pathlib import Path
import re

def expand_file(filepath: Path, included: set[Path], base_dir: Path) -> str:
    result = []
    filepath = filepath.resolve()

    if filepath in included:
        result.append(f"// already included: {filepath}")
        return "\n".join(result)

    included.add(filepath)

    try:
        with open(filepath, "r") as f:
            for line in f:
                stripped = line.strip()
                match = re.match(r'#include\s+"([^"]+)"', stripped)
                if match:
                    include_path = match.group(1)
                    include_path = stripped.split('"')[1]
                    include_file = (filepath.parent / include_path).resolve()
                    if include_file.is_file():
                        result.append(f"// begin include {include_path}")
                        result.append(expand_file(include_file, included, base_dir))
                        result.append(f"// end include {include_path}")
                    else:
                        result.append(f"// include not found: {include_path}")
                else:
                    result.append(line.rstrip())
    except Exception as e:
        result.append(f"// error reading {filepath}: {e}")

    return "\n".join(result)

def main():
    if len(sys.argv) != 2:
        print("Usage: python expand_local_includes.py <file.cpp>")
        sys.exit(1)

    entry_file = Path(sys.argv[1])
    if not entry_file.exists():
        print(f"File {entry_file} does not exist.")
        sys.exit(1)

    output = expand_file(entry_file, included=set(), base_dir=entry_file.parent)
    print(output)

if __name__ == "__main__":
    main()
