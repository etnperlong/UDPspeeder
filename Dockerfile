FROM gcc:14.2 AS builder

WORKDIR /usr/src

COPY . .

RUN set -ex; \
    apt-get update; \
    apt-get install -y --no-install-recommends cmake git; \
    cmake -B build -DCMAKE_BUILD_TYPE=Release; \
    echo "const char *gitversion = \"$(git rev-parse HEAD)\";" > git_version.h; \
    cmake --build build --config Release;

FROM gcr.io/distroless/cc-debian12 AS dist
COPY --from=builder /usr/src/build/speederv2 /speederv2
ENTRYPOINT [ "/speederv2" ]