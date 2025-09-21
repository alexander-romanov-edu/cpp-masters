{
  description = "cpp-masters";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-parts.url = "github:hercules-ci/flake-parts";
    treefmt-nix = {
      url = "github:numtide/treefmt-nix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs =
    { flake-parts, treefmt-nix, ... }@inputs:
    flake-parts.lib.mkFlake { inherit inputs; } {
      imports = [ treefmt-nix.flakeModule ];

      systems = [
        "x86_64-linux"
        "aarch64-linux"
      ];

      perSystem =
        { pkgs, ... }:
        let
          llvmPackages = pkgs.llvmPackages_21;
        in
        {
          imports = [ ./nix/treefmt.nix ];

          devShells.default = (pkgs.mkShell.override { stdenv = llvmPackages.stdenv; }) {
            nativeBuildInputs = with pkgs; [
              meson
              pkg-config
              cmake
              just
              valgrind
              gdb
              ninja
            ];
            buildInputs = with pkgs; [
              boost
              fmt
              gbenchmark
              gtest
            ];
          };
        };
    };
}
