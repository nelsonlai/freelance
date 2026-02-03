package ca.medontime.mycomposeapiapp

import retrofit2.http.GET
import retrofit2.Response

interface ApiService {
    @GET("users")   // Example endpoint
    suspend fun getUsers(): Response<List<User>>
}
