
import { readFileSync } from 'fs';

interface Config {
    node_id: number;
    datacenter_id: number;
    region: number;
    subnet: number;
}

function loadConfig(): Config {
    const data = readFileSync('./config/config.json', 'utf8');
    return JSON.parse(data);
}

export default loadConfig;
