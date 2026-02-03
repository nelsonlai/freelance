package com.example.demo.config;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.core.userdetails.User;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.crypto.factory.PasswordEncoderFactories;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.security.provisioning.InMemoryUserDetailsManager;
import org.springframework.security.web.SecurityFilterChain;

/**
 * Spring Security configuration.
 * <p>
 * Defines which paths require authentication and which are public. Uses HTTP Basic for API auth.
 * In-memory users are for demo only; in production use a database-backed {@link UserDetailsService}.
 */
@Configuration
@EnableWebSecurity
public class SecurityConfig {

    /**
     * Configures the security filter chain: URL authorization and HTTP Basic.
     * <ul>
     *   <li>/api/public/** — permitAll (no auth)</li>
     *   <li>/api/admin/** — hasRole("ADMIN")</li>
     *   <li>/api/** — authenticated (any logged-in user)</li>
     *   <li>anyRequest() — permitAll (e.g. actuator, static resources if any)</li>
     * </ul>
     * CSRF is disabled for /api/** because we use stateless HTTP Basic for APIs.
     */
    @Bean
    public SecurityFilterChain filterChain(HttpSecurity http) throws Exception {
        http
            .authorizeHttpRequests(auth -> auth
                .requestMatchers("/api/public/**").permitAll()
                .requestMatchers("/api/admin/**").hasRole("ADMIN")
                .requestMatchers("/api/**").authenticated()
                .anyRequest().permitAll()
            )
            .httpBasic()
            .and()
            .csrf(csrf -> csrf.ignoringRequestMatchers("/api/**"));
        return http.build();
    }

    /**
     * In-memory user details for demo. In production, use a {@link UserDetailsService} that loads from DB.
     * Passwords are encoded with the delegating password encoder (e.g. BCrypt); never store plain text.
     * {@code roles("USER")} adds authority "ROLE_USER"; hasRole("ADMIN") checks for "ROLE_ADMIN".
     */
    @Bean
    public UserDetailsService userDetailsService(PasswordEncoder passwordEncoder) {
        var user = User.builder()
            .username("user")
            .password(passwordEncoder.encode("password"))
            .roles("USER")
            .build();
        var admin = User.builder()
            .username("admin")
            .password(passwordEncoder.encode("admin"))
            .roles("USER", "ADMIN")
            .build();
        return new InMemoryUserDetailsManager(user, admin);
    }

    /**
     * Delegating password encoder: supports multiple algorithms (e.g. bcrypt, noop for legacy).
     * New passwords should be stored with a strong algorithm (e.g. BCrypt, default in createDelegatingPasswordEncoder).
     */
    @Bean
    public PasswordEncoder passwordEncoder() {
        return PasswordEncoderFactories.createDelegatingPasswordEncoder();
    }
}
