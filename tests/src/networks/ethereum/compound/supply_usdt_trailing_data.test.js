import { nano_models, processTest, populateTransaction } from "../../../../test.fixture";

const contractName = "Morpho";
const contractAddr = "0x8888882f8f843896699869179fb6e4f7e3b58888";
const testNetwork = "ethereum";

const testLabel = "supply usdt trailing data"; // <= Name of the test
const testDirSuffix = testLabel.toLowerCase().replace(/\s+/g, '_');

const inputData = "0x0c0a769b000000000000000000000000f650c3d88d12db855b8bf7d11be6c55a4e07dcc9000000000000000000000000DAD77910DBDFDE764FC21FCD4E74D71BBACA6D8D0000000000000000000000000000000000000000000000000000000005f56bd00000000000000000000000000000000000000000000000000000018a504d338b00000000000000000000000000000000000000000000000000004c6564676572";

const models = [
    {
        name: 'nanosp',
        steps: 4
    },
]

// populate unsignedTx from genericTx and get network chain id
const unsignedTx = populateTransaction(contractAddr, inputData, testNetwork);
// Process tests for each nano models
models.forEach((model) => {
    const nano_model = nano_models.find((nano_model) => nano_model.name === model.name)
    processTest(nano_model, model.steps, contractName, testLabel, testDirSuffix, unsignedTx, testNetwork)
})