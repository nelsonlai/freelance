package com.csvtoexcel;

import org.apache.commons.csv.CSVFormat;
import org.apache.commons.csv.CSVParser;
import org.apache.commons.csv.CSVRecord;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.ss.usermodel.Sheet;
import org.apache.poi.ss.usermodel.Workbook;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.stream.StreamSupport;

/**
 * Reads multiple CSV files from a directory and writes them into a single Excel (.xlsx) file.
 * Each CSV file becomes one sheet in the workbook.
 */
public class CsvToExcel {

    private static final int MAX_SHEET_NAME_LENGTH = 31;
    private static final String DEFAULT_OUTPUT = "output.xlsx";

    public static void main(String[] args) {
        Path inputDir;
        Path outputFile;

        if (args.length >= 2) {
            inputDir = Paths.get(args[0]);
            outputFile = Paths.get(args[1]);
        } else if (args.length == 1) {
            inputDir = Paths.get(args[0]);
            outputFile = Paths.get(DEFAULT_OUTPUT);
        } else {
            inputDir = Paths.get(".").toAbsolutePath().normalize();
            outputFile = Paths.get(DEFAULT_OUTPUT);
            System.out.println("Usage: java -jar csv-to-excel.jar [<input-directory>] [<output.xlsx>]");
            System.out.println("Using current directory as input and '" + DEFAULT_OUTPUT + "' as output.");
        }

        if (!Files.isDirectory(inputDir)) {
            System.err.println("Error: Input path is not a directory: " + inputDir);
            System.exit(1);
        }

        List<Path> csvFiles = listCsvFiles(inputDir);
        if (csvFiles.isEmpty()) {
            System.err.println("No CSV files found in: " + inputDir);
            System.exit(1);
        }

        System.out.println("Found " + csvFiles.size() + " CSV file(s). Writing to " + outputFile + " ...");

        try {
            writeCsvFilesToExcel(csvFiles, outputFile);
            System.out.println("Done. Output: " + outputFile.toAbsolutePath());
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
            e.printStackTrace();
            System.exit(1);
        }
    }

    private static List<Path> listCsvFiles(Path directory) throws IOException {
        List<Path> result = new ArrayList<>();
        try (DirectoryStream<Path> stream = Files.newDirectoryStream(directory, "*.csv")) {
            StreamSupport.stream(stream.spliterator(), false)
                    .sorted(Comparator.comparing(Path::getFileName, String.CASE_INSENSITIVE_ORDER))
                    .forEach(result::add);
        }
        return result;
    }

    private static void writeCsvFilesToExcel(List<Path> csvFiles, Path outputPath) throws IOException {
        try (Workbook workbook = new XSSFWorkbook()) {
            for (Path csvPath : csvFiles) {
                String sheetName = sanitizeSheetName(csvPath.getFileName().toString());
                Sheet sheet = workbook.createSheet(sheetName);
                writeCsvToSheet(csvPath, sheet);
            }
            try (var out = Files.newOutputStream(outputPath)) {
                workbook.write(out);
            }
        }
    }

    private static void writeCsvToSheet(Path csvPath, Sheet sheet) throws IOException {
        CSVFormat format = CSVFormat.DEFAULT.builder()
                .setHeader()
                .setSkipHeaderRecord(true)
                .setIgnoreEmptyLines(true)
                .build();

        try (var reader = new InputStreamReader(Files.newInputStream(csvPath), StandardCharsets.UTF_8);
             CSVParser parser = new CSVParser(reader, format)) {

            int rowNum = 0;
            // Write header if present
            if (parser.getHeaderMap() != null && !parser.getHeaderMap().isEmpty()) {
                Row headerRow = sheet.createRow(rowNum++);
                List<String> headers = parser.getHeaderNames();
                for (int i = 0; i < headers.size(); i++) {
                    headerRow.createCell(i).setCellValue(headers.get(i));
                }
            }
            // Write data rows
            for (CSVRecord record : parser) {
                Row row = sheet.createRow(rowNum++);
                for (int i = 0; i < record.size(); i++) {
                    String value = record.get(i);
                    row.createCell(i).setCellValue(value != null ? value : "");
                }
            }
        }
    }

    private static String sanitizeSheetName(String fileName) {
        // Remove .csv extension
        String name = fileName;
        if (name.toLowerCase().endsWith(".csv")) {
            name = name.substring(0, name.length() - 4);
        }
        // Excel sheet name: no \ / * ? [ ] :
        name = name.replaceAll("[\\\\/*?\\[\\]:]", "_");
        if (name.length() > MAX_SHEET_NAME_LENGTH) {
            name = name.substring(0, MAX_SHEET_NAME_LENGTH);
        }
        return name.isEmpty() ? "Sheet" : name;
    }
}
