package com.example.demo.dto;

/**
 * Data Transfer Object (DTO) for application metadata returned by the /info endpoint.
 * <p>
 * Jackson serializes this to JSON; getter/setter names follow JavaBeans convention
 * so properties appear as "application", "version", "status" in the JSON response.
 */
public class AppInfo {

    /** Display name of the application. */
    private String application;
    /** Version string (e.g. "1.0"). */
    private String version;
    /** Runtime status (e.g. "running"). */
    private String status;

    /** No-argument constructor; required for Jackson deserialization if used for request body. */
    public AppInfo() {}

    /**
     * All-args constructor for building an instance with known values.
     *
     * @param application application name
     * @param version     version string
     * @param status      status string
     */
    public AppInfo(String application, String version, String status) {
        this.application = application;
        this.version = version;
        this.status = status;
    }

    public String getApplication() {
        return application;
    }

    public void setApplication(String application) {
        this.application = application;
    }

    public String getVersion() {
        return version;
    }

    public void setVersion(String version) {
        this.version = version;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }
}
