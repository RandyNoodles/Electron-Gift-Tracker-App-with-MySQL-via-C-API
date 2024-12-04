import { spawn } from 'child_process';


export function MySQLAPI(args){
    const exePath = './C_API/C_API.exe'

    return new Promise((resolve, reject) =>{
        //Build command string

        const child = spawn(exePath, args);

        let stdout = '';
        let stderr = '';

        child.stdout.on('data', (output) => {
            stdout += output.toString();
        });
        child.stderr.on('data', (err) =>{
            console.log(err.toString());
            stderr += err.toString();
        });


        //Resolve/reject promise based on 0/nonzero exit code
        child.on('close', (exitCode) =>{

            //True success
            if(exitCode === 0 && stderr === ''){
                resolve({ success: true, api_output: stdout});
            }
            //Mismatched exit code, return error logs.
            else if(exitCode === 0 && stderr !== ''){
                resolve({success: false, api_output: stderr});
            }
            else{
                //Exceptions should be written to stderr
                reject({ success: false, api_output: stderr});
            }
        });
        
        //This means things have gone very wrong.
        child.on('error', (output) => {
            reject({success: false, api_output: `Database API call failed: ${output.message}`});
        })
    });
}