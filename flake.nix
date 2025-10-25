{
  description = "mex: discord bot for Muhamix, written in C++";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    git-hooks.url = "github:cachix/git-hooks.nix";
  };

  outputs =
    inputs@{ self, nixpkgs, ... }:
    let
      supportedSystems = [
        "x86_64-linux"
        "aarch64-linux"
        "x86_64-darwin"
        "aarch64-darwin"
      ];

      forSystems =
        f:
        nixpkgs.lib.genAttrs supportedSystems (
          system:
          f {
            system = system;
            pkgs = import nixpkgs { inherit system; };
          }
        );
    in
    {
      formatter = forSystems (
        { pkgs, system }:
        let
          config = self.checks.${system}.pre-commit-check.config;
          inherit (config) package configFile;
          script = ''
            ${package}/bin/pre-commit run --all-files --config ${configFile}
          '';
        in
        pkgs.writeShellScriptBin "pre-commit-run" script
      );

      checks = forSystems (
        { pkgs, system }:
        {
          pre-commit-check = inputs.git-hooks.lib.${system}.run {
            src = ./.;
            hooks = {
              clang-format = {
                enable = true;
                types_or = pkgs.lib.mkForce [
                  "c"
                  "c++"
                ];
              };
              nixfmt-rfc-style.enable = true;
            };
          };
        }
      );

      devShells = forSystems (
        { pkgs, system }:
        {
          default =
            let
              inherit (pkgs)
                mkShell
                clangStdenv
                clang-tools
                dpp
                ;
              inherit (self.checks.${system}.pre-commit-check) shellHook enabledPackages;
            in
            mkShell.override { stdenv = clangStdenv; } {
              name = "mex";
              inherit shellHook;
              packages = [
                clang-tools
                dpp
              ]
              ++ enabledPackages;
            };
        }
      );
    };
}
