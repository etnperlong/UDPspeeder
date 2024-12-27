FROM gcc:14.2 AS builder

WORKDIR /usr/src

COPY . .

RUN set -ex; \
    apt-get update; \
    apt-get install -y --no-install-recommends cmake; \
    cmake -B build -DCMAKE_BUILD_TYPE=Release .; \
    make;

FROM gcr.io/distroless/cc-debian12 AS dist
COPY --from=builder /usr/src/speederv2 /speederv2
ENTRYPOINT [ "/speederv2" ]