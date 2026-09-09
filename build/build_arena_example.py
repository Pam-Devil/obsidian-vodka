from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parent.parent

try:
    command = [
        "gcc",
        str(ROOT / "examples/arena_example.c"),
        str(ROOT / "src/dataStructures/stack.c"),
        str(ROOT / "src/strategies/arena.c"),
        str(ROOT / "src/allocator.c"),
        f"-I{ROOT / 'include'}",
        f"-I{ROOT / 'include/dataStructures'}",
        f"-I{ROOT / 'include/strategies'}",
        "-o",
        str(ROOT / "bin/test_arena_allocation.exe"),
    ]
    subprocess.run(command, check=True, text=True, capture_output=True)
    print("Programa compilado com sucesso");
except subprocess.CalledProcessError as e:
    print(f"Erro ao compilar os testes: {e.stderr}")