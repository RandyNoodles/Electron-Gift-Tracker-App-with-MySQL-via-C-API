import { exec } from 'child_process';

const exePath = './C_API.exe'

export function MySQLAPI(queryEnum, args){
    return new Promise((resolve, reject) =>{
        //Build command string
        const command = `${exePath} ${queryEnum} ${args.join(' ')}`;

        exec(command, (error, stdout, stderr) =>{
            if(error){
                reject(new Error(`${stderr || error.message}`));
            }
            else{
                resolve(stdout.trim);
            }
        })

    })
}