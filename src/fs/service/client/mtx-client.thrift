namespace cpp com.twitter.service.snowflake.gen

service mtxClient {
    // Defina seus métodos aqui
    i64 getUniqueId(1: string key);
}
