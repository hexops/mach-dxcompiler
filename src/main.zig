const c = @cImport(
    @cInclude("mach_dxc.h"),
);

test {
    c.machDxcFoo();
}
