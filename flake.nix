{
  description = "Muhamix's open-source discord bot";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
  };

  outputs =
    { self, nixpkgs }:
    let
      system = "x86_64-linux"; # CHANGE THIS DEPENDING ON YOUR SYSTEM
      pkgs = import nixpkgs {
        inherit system;
      };
    in
    {
      devShells.${system}.default = pkgs.mkShell {
        packages =
          let
            inherit (pkgs) typescript-language-server nodePackages_latest nodejs;
          in
          [
            nodePackages_latest.ts-node
            typescript-language-server
            nodejs
          ];
      };

    };
}
