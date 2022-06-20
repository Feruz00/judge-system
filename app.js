const express = require('express');
const dotenv = require("dotenv")
const morgan = require('morgan')
const cors = require('cors')

// Load env 
dotenv.config({path: "./config.env"})

const app = express();

// bodyparser
app.use(express.json({ limit: "50mb"}));
app.use(express.urlencoded({extended: true, limit:"50mb", parameterLimit: 50000}));

// cors

app.use(cors())

if (process.env.NODE_ENV === "development") {
    app.use(morgan("tiny"));
}

app.use('/api/problem', require('./routes/problem'))

const PORT = process.env.PORT || 8080;

app.listen(PORT, () => {

    console.log(`Judge Server running in ${process.env.NODE_ENV} mode on port ${PORT}`)
});