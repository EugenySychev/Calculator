package org.sychev.calculator.ui

import android.content.res.Configuration
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.text.BasicTextField
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalConfiguration
import androidx.compose.ui.text.TextRange
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontStyle
import androidx.compose.ui.text.input.TextFieldValue
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import org.sychev.calculator.CalculatorState
import org.sychev.calculator.CalculatorViewModel
import org.sychev.calculator.ui.theme.*

@Composable
fun CalculatorScreen(viewModel: CalculatorViewModel) {
    val state by viewModel.state.collectAsStateWithLifecycle()
    CalculatorContent(
        state = state,
        onButtonClick = viewModel::onButtonClick,
        onCursorMove = viewModel::updateCursorPosition,
        onDirectInput = viewModel::onDirectTextInput,
    )
}

@Composable
private fun CalculatorContent(
    state: CalculatorState,
    onButtonClick: (String) -> Unit,
    onCursorMove: (Int) -> Unit,
    onDirectInput: (String, Int) -> Unit,
) {
    val isLandscape = LocalConfiguration.current.orientation == Configuration.ORIENTATION_LANDSCAPE
    Box(
        modifier = Modifier
            .fillMaxSize()
            .background(Background)
            .systemBarsPadding()
            .imePadding(),
    ) {
        if (isLandscape) {
            LandscapeLayout(state, onButtonClick, onCursorMove, onDirectInput)
        } else {
            PortraitLayout(state, onButtonClick, onCursorMove, onDirectInput)
        }
    }
}

// ── Portrait ──────────────────────────────────────────────────────────────────

@Composable
private fun PortraitLayout(
    state: CalculatorState,
    onButtonClick: (String) -> Unit,
    onCursorMove: (Int) -> Unit,
    onDirectInput: (String, Int) -> Unit,
) {
    Column(modifier = Modifier.fillMaxSize()) {
        DisplayArea(
            state = state,
            onCursorMove = onCursorMove,
            onDirectInput = onDirectInput,
            onSciToggle = { onButtonClick("Sci") },
            modifier = Modifier.fillMaxWidth().weight(1f),
        )
        ButtonGrid(
            state = state,
            isLandscape = false,
            showSciRows = state.isScientificMode,
            onButtonClick = onButtonClick,
            modifier = Modifier.fillMaxWidth().padding(horizontal = 4.dp, vertical = 4.dp),
        )
    }
}

// ── Landscape ─────────────────────────────────────────────────────────────────
//  Portrait: display on top, buttons below (square).
//  Landscape: display left, buttons right (fill height).
//  When sci is ON in landscape, sci buttons go into the left (display) column.

@Composable
private fun LandscapeLayout(
    state: CalculatorState,
    onButtonClick: (String) -> Unit,
    onCursorMove: (Int) -> Unit,
    onDirectInput: (String, Int) -> Unit,
) {
    val leftWeight = if (state.isScientificMode) 0.50f else 0.38f

    Row(modifier = Modifier.fillMaxSize()) {
        // Left column: display area (+ sci buttons when sci ON)
        Column(
            modifier = Modifier
                .weight(leftWeight)
                .fillMaxHeight(),
        ) {
            DisplayArea(
                state = state,
                onCursorMove = onCursorMove,
                onDirectInput = onDirectInput,
                onSciToggle = { onButtonClick("Sci") },
                modifier = Modifier
                    .fillMaxWidth()
                    .weight(if (state.isScientificMode) 0.38f else 1f),
            )
            if (state.isScientificMode) {
                SciBtnGrid(
                    isDegMode = state.isDegMode,
                    isLandscape = true,
                    onButtonClick = onButtonClick,
                    modifier = Modifier
                        .fillMaxWidth()
                        .weight(0.62f)
                        .padding(start = 4.dp, bottom = 4.dp),
                )
            }
        }

        // Right column: basic buttons always, fill height equally across 6 rows
        ButtonGrid(
            state = state,
            isLandscape = true,
            showSciRows = false,
            onButtonClick = onButtonClick,
            modifier = Modifier
                .weight(1f - leftWeight)
                .fillMaxHeight()
                .padding(end = 4.dp, bottom = 4.dp),
        )
    }
}

// ── Display area ──────────────────────────────────────────────────────────────

@Composable
private fun DisplayArea(
    state: CalculatorState,
    onCursorMove: (Int) -> Unit,
    onDirectInput: (String, Int) -> Unit,
    onSciToggle: () -> Unit,
    modifier: Modifier = Modifier,
) {
    var tfv by remember {
        mutableStateOf(TextFieldValue(state.expression, TextRange(state.cursorPosition)))
    }

    LaunchedEffect(state.expression, state.cursorPosition) {
        if (tfv.text != state.expression || tfv.selection.end != state.cursorPosition) {
            tfv = TextFieldValue(state.expression, TextRange(state.cursorPosition))
        }
    }

    Column(
        modifier = modifier.padding(horizontal = 16.dp, vertical = 8.dp),
        verticalArrangement = Arrangement.Bottom,
        horizontalAlignment = Alignment.End,
    ) {
        Row(
            modifier = Modifier.fillMaxWidth(),
            horizontalArrangement = Arrangement.SpaceBetween,
            verticalAlignment = Alignment.CenterVertically,
        ) {
            TextButton(onClick = onSciToggle) {
                Text(
                    text = if (state.isScientificMode) "Basic" else "Sci",
                    color = AccentBlue,
                    fontSize = 15.sp,
                )
            }
            Text(
                text = "M",
                color = if (state.memoryEmpty) TextDisabled else TextPrimary,
                fontSize = 20.sp,
                modifier = Modifier.padding(end = 4.dp),
            )
        }

        Spacer(modifier = Modifier.weight(1f))

        if (state.result.isNotEmpty()) {
            Text(
                text = state.result,
                color = TextSecondary,
                fontSize = 24.sp,
                fontStyle = FontStyle.Italic,
                textAlign = TextAlign.End,
                modifier = Modifier.fillMaxWidth().padding(bottom = 4.dp),
            )
        }

        BasicTextField(
            value = tfv,
            onValueChange = { newValue ->
                tfv = newValue
                if (newValue.text != state.expression) {
                    onDirectInput(newValue.text, newValue.selection.end)
                } else {
                    onCursorMove(newValue.selection.end)
                }
            },
            textStyle = TextStyle(
                color = TextPrimary,
                fontSize = 30.sp,
                textAlign = TextAlign.End,
            ),
            singleLine = true,
            modifier = Modifier.fillMaxWidth().padding(bottom = 8.dp),
        )
    }
}

// ── Button grids ──────────────────────────────────────────────────────────────

@Composable
private fun ButtonGrid(
    state: CalculatorState,
    isLandscape: Boolean,
    showSciRows: Boolean,
    onButtonClick: (String) -> Unit,
    modifier: Modifier = Modifier,
) {
    Column(modifier = modifier) {
        if (showSciRows) {
            SciBtnGrid(
                isDegMode = state.isDegMode,
                isLandscape = isLandscape,
                onButtonClick = onButtonClick,
            )
        }
        CalcRow(isLandscape) {
            listOf("MR", "MC", "M+", "M-").forEach { b ->
                CalcBtn(b, SurfaceMem, isLandscape) { onButtonClick(b) }
            }
        }
        CalcRow(isLandscape) {
            listOf("(", ")", "←", "C").forEach { b ->
                CalcBtn(b, SurfaceMem, isLandscape) { onButtonClick(b) }
            }
        }
        CalcRow(isLandscape) {
            listOf("7", "8", "9").forEach { b -> CalcBtn(b, SurfaceNum, isLandscape) { onButtonClick(b) } }
            CalcBtn("/", AccentOrange, isLandscape) { onButtonClick("/") }
        }
        CalcRow(isLandscape) {
            listOf("4", "5", "6").forEach { b -> CalcBtn(b, SurfaceNum, isLandscape) { onButtonClick(b) } }
            CalcBtn("*", AccentOrange, isLandscape) { onButtonClick("*") }
        }
        CalcRow(isLandscape) {
            listOf("1", "2", "3").forEach { b -> CalcBtn(b, SurfaceNum, isLandscape) { onButtonClick(b) } }
            CalcBtn("-", AccentOrange, isLandscape) { onButtonClick("-") }
        }
        CalcRow(isLandscape) {
            CalcBtn("0", SurfaceNum, isLandscape) { onButtonClick("0") }
            CalcBtn(",", SurfaceNum, isLandscape) { onButtonClick(",") }
            CalcBtn("=", AccentBlue, isLandscape) { onButtonClick("=") }
            CalcBtn("+", AccentOrange, isLandscape) { onButtonClick("+") }
        }
    }
}

@Composable
private fun SciBtnGrid(
    isDegMode: Boolean,
    isLandscape: Boolean,
    onButtonClick: (String) -> Unit,
    modifier: Modifier = Modifier,
) {
    Column(modifier = modifier) {
        CalcRow(isLandscape) {
            listOf("sin", "cos", "tan", "asin", "acos", "atan").forEach { b ->
                CalcBtn(b, SurfaceFn, isLandscape) { onButtonClick(b) }
            }
        }
        CalcRow(isLandscape) {
            listOf("log", "ln", "√", "x^n", "!", "%").forEach { b ->
                CalcBtn(b, SurfaceFn, isLandscape) { onButtonClick(b) }
            }
        }
        CalcRow(isLandscape) {
            listOf("e", "π", "mod", "|x|").forEach { b ->
                CalcBtn(b, SurfaceFn, isLandscape) { onButtonClick(b) }
            }
            val degRadLabel = if (isDegMode) "Deg" else "Rad"
            CalcBtn(degRadLabel, SurfaceFn, isLandscape) { onButtonClick(degRadLabel) }
        }
    }
}

// ── Primitives ────────────────────────────────────────────────────────────────
// CalcRow / CalcBtn are scope-aware extension functions so Modifier.weight() resolves correctly.

@Composable
private fun ColumnScope.CalcRow(
    isLandscape: Boolean,
    content: @Composable RowScope.() -> Unit,
) {
    Row(
        modifier = (if (isLandscape) Modifier.weight(1f) else Modifier)
            .fillMaxWidth()
            .padding(vertical = 2.dp),
        horizontalArrangement = Arrangement.spacedBy(4.dp),
        content = content,
    )
}

@Composable
private fun RowScope.CalcBtn(
    text: String,
    color: androidx.compose.ui.graphics.Color,
    isLandscape: Boolean,
    onClick: () -> Unit,
) {
    Button(
        onClick = onClick,
        modifier = (if (isLandscape) Modifier.fillMaxHeight() else Modifier.aspectRatio(1f))
            .weight(1f)
            .padding(2.dp),
        colors = ButtonDefaults.buttonColors(containerColor = color),
        shape = MaterialTheme.shapes.medium,
        contentPadding = PaddingValues(0.dp),
    ) {
        Text(
            text = text,
            color = TextPrimary,
            fontSize = 15.sp,
            textAlign = TextAlign.Center,
            maxLines = 1,
        )
    }
}

// ── Previews ──────────────────────────────────────────────────────────────────

@Preview(showBackground = true, widthDp = 380, heightDp = 820)
@Composable
private fun PortraitPreview() {
    CalculatorTheme {
        CalculatorContent(
            state = CalculatorState(expression = "sin(π)", result = "0"),
            onButtonClick = {}, onCursorMove = {}, onDirectInput = { _, _ -> },
        )
    }
}

@Preview(showBackground = true, widthDp = 820, heightDp = 380)
@Composable
private fun LandscapePreview() {
    CalculatorTheme {
        CalculatorContent(
            state = CalculatorState(expression = "2+2", result = "4"),
            onButtonClick = {}, onCursorMove = {}, onDirectInput = { _, _ -> },
        )
    }
}

@Preview(showBackground = true, widthDp = 820, heightDp = 380)
@Composable
private fun LandscapeSciPreview() {
    CalculatorTheme {
        CalculatorContent(
            state = CalculatorState(expression = "sin(π/2)", result = "1", isScientificMode = true),
            onButtonClick = {}, onCursorMove = {}, onDirectInput = { _, _ -> },
        )
    }
}
