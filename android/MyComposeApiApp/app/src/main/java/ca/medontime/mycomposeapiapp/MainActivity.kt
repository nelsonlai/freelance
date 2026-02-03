package ca.medontime.mycomposeapiapp

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.Column
import androidx.compose.runtime.getValue
import androidx.compose.foundation.lazy.items
import androidx.compose.material3.Card
import androidx.compose.material3.CardDefaults
import androidx.compose.material3.Text
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.TopAppBar
import androidx.compose.material3.Scaffold
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp
import androidx.compose.ui.tooling.preview.Preview
import androidx.lifecycle.viewmodel.compose.viewModel
import androidx.compose.runtime.collectAsState
import androidx.compose.ui.Alignment


import ca.medontime.mycomposeapiapp.User
import ca.medontime.mycomposeapiapp.ui.theme.MyComposeApiAppTheme

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            MyComposeApiAppTheme {
                UserScreen()
            }
        }
    }
}

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun UserScreen(userViewModel: UserViewModel = viewModel()) { // Use viewModel() to get an instance
    val users by userViewModel.users.collectAsState()

    Scaffold(
        topBar = {
            TopAppBar(title = { Text("Users from API") })
        }
    ) { paddingValues ->
        if (users.isEmpty()) {
            Box(
                modifier = Modifier
                    .fillMaxSize()
                    .padding(paddingValues),
                contentAlignment = Alignment.Center
            ) {
                Text("Loading users or no users found ...")
            }
        } else {
            LazyColumn(modifier = Modifier.padding(paddingValues)) {
                items(users) { user ->
                    UserListItem(user)
                }
            }
        }
    }
}

@Preview(showBackground = true)
@Composable
fun UserListItem(user: User) {
    Card(
        modifier = Modifier
            .fillMaxWidth()
            .padding(8.dp),
        elevation = CardDefaults.cardElevation(defaultElevation = 4.dp)
    ) {
        Column(
            modifier = Modifier
                .fillMaxWidth()
                .padding(16.dp)
        ) {
            Text(text = "ID: ${user.id}")
            Text(text = "Name: ${user.name}")
            Text(text = "Username: ${user.username}")
            Text(text = "Email: ${user.email}")
        }
    }
}