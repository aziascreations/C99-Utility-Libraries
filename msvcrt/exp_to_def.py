import os
import re
import sys

from pathlib import Path

EXP_REGEX = re.compile('^([0-9]+) +([0-9A-F]+) +([0-9A-F]+) +(.*)$', re.IGNORECASE)


def main(input_exp_path: str, output_def_path: str, do_overwrite_def: bool = True) -> None:
    if os.path.exists(output_def_path):
        if do_overwrite_def:
            os.remove(output_def_path)

    with open(input_exp_path, "r") as f:
        raw_definition_lines = f.readlines()

    valid_definition_lines = list()
    for raw_def_line in raw_definition_lines:
        raw_def_line = raw_def_line.strip()
        if len(raw_def_line) == 0:
            continue
        if not EXP_REGEX.match(raw_def_line):
            continue
        _raw_def_line_parts = EXP_REGEX.search(raw_def_line).group(4)
        if _raw_def_line_parts:
            valid_definition_lines.append(_raw_def_line_parts)

    # Can happen with some bad/stub DLL that Microsoft ships.
    if len(valid_definition_lines) == 0:
        return

    with open(output_def_path, "w") as f:
        f.write("LIBRARY {}.dll\n".format(Path(input_exp_path).stem))
        f.write("\n")
        f.write("EXPORTS\n")
        for valid_def_line in valid_definition_lines:
            if " " in valid_def_line:
                continue
            if valid_def_line.startswith("?"):
                continue
            f.write("{}\n".format(valid_def_line))


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("ERROR: Invalid launch parameters given to 'exp_to_def.py' !")
        sys.exit(1)

    if not os.path.exists(sys.argv[1]):
        print("ERROR: The file '{}' couldn't be found in '{}' !".format(sys.argv[1], os.cwd()))
        sys.exit(1)

    try:
        main(sys.argv[1], sys.argv[2])
    except Exception as err:
        print("ERROR: Failed to process '{}' !".format(sys.argv[1]))
        print(err)
        sys.exit(1)
    sys.exit(0)
