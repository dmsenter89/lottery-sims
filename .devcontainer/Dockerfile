# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.245.2/containers/alpine/.devcontainer/base.Dockerfile

# [Choice] Alpine version: 3.16, 3.15, 3.14, 3.13
ARG VARIANT="3.16"
FROM mcr.microsoft.com/vscode/devcontainers/base:0-alpine-${VARIANT}

# ** [Optional] Uncomment this section to install additional packages. **
 RUN apk update \
     && apk add --no-cache cargo exa g++ go hyperfine openmp-dev py3-numpy py3-pip python3 make rust rustfmt

USER vscode

# Update Go packages for the Go extension
RUN go install golang.org/x/tools/gopls@latest \
    && go install honnef.co/go/tools/cmd/staticcheck@latest \
    && go install github.com/go-delve/delve/cmd/dlv@latest

# Add Julia Support
RUN curl https://julialang-s3.julialang.org/bin/musl/x64/1.8/julia-1.8.2-musl-x86_64.tar.gz | tar -xz -C /home/vscode \
    && /home/vscode/julia-1.8.2/bin/julia -E 'using Pkg; Pkg.add("StatsBase"); Pkg.precompile()'