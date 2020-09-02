{ pkgs ? import <nixpkgs> { } }: pkgs.stdenv.mkDerivation {
  name = "gltest";
  src = builtins.path {
    name = "gltest";
    path = ./.;
  };
  buildInputs = [ pkgs.glew pkgs.glfw ];
}
