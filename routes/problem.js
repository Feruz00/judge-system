const router = require('express').Router();
const axios = require('axios');
const Submission = require('../models/submission');
const path = require('path')

const multer = require('multer');
const addSubmission = require('../judge');

const upload = multer({
    fileFilter: function(req, file, cb){
        const filetypes = /text|txt|cpp|c|py|java/;
        const mimetype = filetypes.test(file.mimetype)
        const extname = filetypes.test(path.extname(file.originalname).toLocaleLowerCase())
        
        if(mimetype && extname){
            return cb(null, true);
        }
        return cb(new Error("Only text files are allowed"))
    },
    storage: multer.memoryStorage()
}).fields([
    { name: 'solutionFile', maxCount: 1 },
    { name: 'inputTests', maxCount: 1000 },
    { name: 'outputTests', maxCount: 1000 }
])

router.post('/', upload,  (req, res) => {
    
    const solution = req.files.solutionFile[0].buffer.toString();

    const input = req.files.inputTests.map( i=> i.buffer.toString() );
    const output = req.files.outputTests.map( i=> i.buffer.toString() );
    
    const systemTestCases = input.map( (i,index)=>({input: i, output: output[index]}) )

    const problem={
        name: req.body.problemName,
        tests: systemTestCases,
        solution,
        time: req.body.time,
        memory: req.body.memory
    }

    const submission = new Submission({
        problemName: problem.name,
        code: solution,
        language: path
          .extname(req.files.solutionFile[0].originalname)
          .split(".")[1],
    });

    addSubmission(problem,submission, "submit", (err, result)=>{
        if (err)
        return res
          .status(500)
          .json({ message: "Something Went Wrong! Try Again!!!" });

        return res.json({result})
    } )
    
    //         addSubmission(problem, submission, "submit", (err, result) => {
    //             if (err)
    //               return res
    //                 .status(500)
    //                 .json({ message: "Something Went Wrong! Try Again!!!" });
      
    //             let flag = false;
      
    //             result.every((curResult) => {
    //               let verdict;
    //               for (let key in curResult) {
    //                 if (curResult[key] === true) {
    //                   verdict = key;
    //                 }
    //               }
      
    //               if (verdict !== "AC") {
    //                 flag = true;
    //                 return false;
    //               } else {
    //                 return true;
    //               }
    //             });
      
    //             if (!flag) {
    //               return res.status(200).json({ problem: problem });
    //             } else {
    //               return res.status(500).json({ message: "Problem rejected." });
    //             }
    //           });
            
    //     })

});
module.exports = router