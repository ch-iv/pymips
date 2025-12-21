from pathlib import Path
from tokenizer import Tokenizer

import unittest

class TestTokenizerSnapshot(unittest.TestCase):
    SAMPLE_EXT = ".asm"
    SNAPSHOT_EXT = ".snapshot"
    SAMPLES_DIR = Path("tests") / "samples"
    SNAPSHOTS_DIR = "snapshots"
    
    def setUp(self):
        self.test_dir = Path(__file__).parent
        self.samples_dir = self.test_dir.parent.parent / self.SAMPLES_DIR
        self.snapshots_dir = self.test_dir / self.SNAPSHOTS_DIR
    
    def _get_snapshot_path(self, sample_path: Path) -> Path:
        return self.snapshots_dir / f"{sample_path.name}{self.SNAPSHOT_EXT}"
    
    def _tokenize_file(self, file_path: Path) -> list[str]:
        source = file_path.read_text()
        tokens = Tokenizer(source).tokenize()
        return [str(token) for token in tokens]
    
    def _load_snapshot(self, snapshot_path: Path) -> list[str] | None:
        if not snapshot_path.exists():
            return None
        return snapshot_path.read_text().splitlines()
    
    def _save_snapshot(self, snapshot_path: Path, tokens: list[str]):
        self.snapshots_dir.mkdir(parents=True, exist_ok=True)
        snapshot_path.write_text('\n'.join(tokens) + '\n')
    
    def generate_snapshot(self, sample_path: Path):
        tokens = self._tokenize_file(sample_path)
        snapshot_path = self._get_snapshot_path(sample_path)
        self._save_snapshot(snapshot_path, tokens)
    
    def generate_all_snapshots(self):
        for sample_path in sorted(self.samples_dir.glob(f"*{self.SAMPLE_EXT}")):
            self.generate_snapshot(sample_path)
    
    def test_tokenizer_snapshots(self):
        for sample_path in sorted(self.samples_dir.glob(f"*{self.SAMPLE_EXT}")):
            with self.subTest(sample=sample_path.name):
                snapshot_path = self._get_snapshot_path(sample_path)
                current_output = self._tokenize_file(sample_path)
                expected_output = self._load_snapshot(snapshot_path)
                
                if expected_output is None:
                    self.skipTest(f"Snapshot not found for {sample_path.name}, generating...")
                
                self.assertListEqual(
                    current_output,
                    expected_output,
                    f"Tokenizer output mismatch for {sample_path.name}"
                )

if __name__ == '__main__':
    unittest.main()