import { exec } from 'child_process';


export function MySQLAPI(args){
    const exePath = './C_API.exe'

    return new Promise((resolve, reject) =>{
        //Build command string

        const child = spawn(exePath, args);

        let stdout = '';
        let stderr = '';

        child.stdout.on('data', (output) => {
            stdout += output.toString();
        });
        child.stderr.on('data', (output) =>{
            stderr += output.toString();
        });


        //Resolve/reject promise based on 0/nonzero exit code
        child.on('close', (exitCode) =>{
            if(exitCode === 0){
                //C API should have written to stdout
                resolve({ success: true, output: stdout});
            }
            else{
                //Exceptions should be written to stderr
                reject({ success: false, error: stderr});
            }
        });
        
        //This means things have gone very wrong.
        child.on('error', (output) => {
            reject({success: false, error: `Database API call failed: ${output.message}`});
        })
    });
}