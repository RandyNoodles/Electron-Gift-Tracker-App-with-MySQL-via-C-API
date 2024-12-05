var fs = require('fs');

export function LoadHTML(name){
    
    return new Promise((resolve, reject) =>{

        const filePath = "../HTMLSections/".concat(name);

        let fileContent = '';
        fs.readFile(filePath, function(err, data){
            if(err){
                //Do nothing;
            }
            else{
                fileContent = data;
            }
        });
    
        if(fileContent = ''){
            return 
        }

    })

    


}