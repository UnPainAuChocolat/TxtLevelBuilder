{ pkgs ? import <nixpkgs> {}}:

pkgs.mkShell {
		buildInputs = with pkgs; [
				stdenv.cc
				raylib
				pkg-config
		];
}
