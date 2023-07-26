const std = @import("std");

const print = std.debug.print;
const fs = std.fs;

pub fn main() !void {
    var test_file = "/home/kali/Projects/prepender/LICENSE";
    var elf = is_elf(test_file);
    print("(test): ELF file status: {}\n", .{elf});

    var s = file_size(test_file) catch |err| {
        std.debug.panic("{}", .{err});
    };
    print("(test): File size: {}\n", .{s});

    const fsize = try file_size(test_file);
    const allocator = std.heap.page_allocator;
    const memory = try allocator.alloc(u8, fsize);
    defer allocator.free(memory);

    var file_contents = read_file(test_file, allocator) catch |err| {
        std.debug.panic("{}", .{err});
    };
    print("(test): File contents size: {}\n", .{ file_contents.len });
}

pub fn is_elf(f: []const u8) bool {
    var file = fs.openFileAbsolute(f, .{ .mode = .read_only }) catch |err| {
        std.debug.panic("{}", .{err});
    };
    defer file.close();

    var buffer: [4]u8 = undefined;
    const magic = .{'\x7f', 'E', 'L', 'F'};

    file.seekTo(0) catch |err| {
        std.debug.panic("{}", .{err});
    };
    _ = file.read(&buffer) catch |err| {
        std.debug.panic("{}", .{err});
    };

    return std.mem.eql(comptime u8, &buffer, &magic);
}

pub fn read_file(f: []const u8, allocator: std.mem.Allocator) ![]const u8 {
    var file = try fs.openFileAbsolute(f, .{ .mode = .read_only });
    defer file.close();

    const fsize = try file_size(f);
    return try file.reader().readAllAlloc(allocator, fsize);
}

pub fn file_size(f: []const u8) !u64 {
    var file = try fs.openFileAbsolute(f, .{ .mode = .read_only });
    defer file.close();
        
    var st = try file.stat();
    return st.size;
}
