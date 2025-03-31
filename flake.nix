{
  description = "Rust Result type in C++";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    # need to use flake-utils to get the eachDefaultSystem function
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        pythonEnv = pkgs.python312.withPackages (ps: with ps; [
          meson
        ]);
      in
      {
        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs; [
            pythonEnv
            gcc
            ninja
          ];

          shellHook = ''
            echo "🚀 Development environment loaded!"
            echo "Python version: $(python --version)"
            echo "Meson version: $(meson --version)"
            echo "GCC version: $(gcc --version | head -n1)"
            echo "ninja version: $(ninja --version)"
            echo ""
            echo "Available commands:"
            echo "  meson setup build --buildtype=debug    - Configure debug build"
            echo "  meson setup build --buildtype=release  - Configure release build"
            echo "  meson compile -C build                 - Build the project"
            echo "  meson test -C build                    - Run all tests"
            echo "  ./build/example_name                   - Run a specific example"
            echo ""
            echo "Build types:"
            echo "  debug   - Debug symbols, minimal optimization"
            echo "  release - Full optimization, no debug symbols"
          '';
        };
      }
    );
}