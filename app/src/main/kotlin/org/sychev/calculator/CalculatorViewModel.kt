package org.sychev.calculator

import androidx.lifecycle.ViewModel
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlin.math.abs
import kotlin.math.floor

data class CalculatorState(
    val expression: String = "0",
    val cursorPosition: Int = 1,
    val result: String = "",
    val memoryValue: Double = 0.0,
    val memoryEmpty: Boolean = true,
    val isDegMode: Boolean = false,
    val isScientificMode: Boolean = false,
)

class CalculatorViewModel : ViewModel() {
    private val engine = CalcEngine()
    private val _state = MutableStateFlow(CalculatorState())
    val state: StateFlow<CalculatorState> = _state.asStateFlow()

    fun updateCursorPosition(pos: Int) {
        _state.update { it.copy(cursorPosition = pos) }
    }

    fun onDirectTextInput(text: String, cursor: Int) {
        _state.update { it.copy(expression = text, cursorPosition = cursor) }
    }

    fun onButtonClick(button: String) {
        _state.update { current ->
            when (button) {
                "C" -> current.copy(expression = "0", cursorPosition = 1, result = "")
                "←" -> handleBackspace(current)
                "=" -> handleEquals(current)
                "MR" -> handleMemoryRecall(current)
                "M+" -> handleMemoryAdd(current)
                "M-" -> handleMemorySub(current)
                "MC" -> current.copy(memoryValue = 0.0, memoryEmpty = true)
                "Deg", "Rad" -> current.copy(isDegMode = !current.isDegMode)
                "Sci" -> current.copy(isScientificMode = !current.isScientificMode)
                else -> handleInput(current, button)
            }
        }
    }

    private fun handleBackspace(state: CalculatorState): CalculatorState {
        val text = state.expression
        val pos = state.cursorPosition
        if (pos <= 0) return state
        val newText = (text.substring(0, pos - 1) + text.substring(pos)).ifEmpty { "0" }
        return state.copy(expression = newText, cursorPosition = maxOf(0, pos - 1))
    }

    private fun handleEquals(state: CalculatorState): CalculatorState {
        return try {
            engine.isDegMode = state.isDegMode
            val result = engine.calculate(state.expression)
            state.copy(result = formatResult(result))
        } catch (e: Exception) {
            state.copy(result = "Ошибка")
        }
    }

    private fun handleMemoryRecall(state: CalculatorState): CalculatorState {
        if (state.memoryEmpty) return state
        return insertAtCursor(state, formatResult(state.memoryValue))
    }

    private fun handleMemoryAdd(state: CalculatorState): CalculatorState {
        val value = state.result.toDoubleOrNull() ?: return state
        return state.copy(memoryValue = state.memoryValue + value, memoryEmpty = false)
    }

    private fun handleMemorySub(state: CalculatorState): CalculatorState {
        val value = state.result.toDoubleOrNull() ?: return state
        val newMem = state.memoryValue - value
        return state.copy(memoryValue = newMem, memoryEmpty = newMem == 0.0)
    }

    private fun handleInput(state: CalculatorState, button: String): CalculatorState {
        val text = state.expression
        val pos = state.cursorPosition

        val insertText = when (button) {
            "," -> "."
            "x^n" -> "^"
            "|x|" -> "|"
            "sin", "cos", "tan", "asin", "acos", "atan", "log", "ln", "√" -> "$button("
            else -> button
        }

        // Replace leading "0" when entering a digit or decimal
        if (text == "0" && pos == 1 && (insertText.first().isDigit() || insertText == ".")) {
            return state.copy(expression = insertText, cursorPosition = insertText.length)
        }

        // Prevent consecutive binary operators (allow minus after operator for negation)
        if (insertText in setOf("+", "*", "/") && pos > 0) {
            val prevChar = if (pos <= text.length) text[pos - 1].toString() else ""
            if (prevChar in setOf("+", "-", "*", "/")) {
                val newText = text.substring(0, pos - 1) + insertText + text.substring(pos)
                return state.copy(expression = newText, cursorPosition = pos)
            }
        }

        return insertAtCursor(state, insertText)
    }

    private fun insertAtCursor(state: CalculatorState, text: String): CalculatorState {
        val expr = state.expression
        val pos = state.cursorPosition
        val newExpr = expr.substring(0, pos) + text + expr.substring(pos)
        return state.copy(expression = newExpr, cursorPosition = pos + text.length)
    }

    fun formatResult(value: Double): String {
        if (value.isNaN()) return "NaN"
        if (value.isInfinite()) return if (value > 0) "∞" else "-∞"
        if (value == floor(value) && abs(value) < 1e15) return value.toLong().toString()
        return "%.10f".format(value).trimEnd('0').trimEnd('.')
    }
}
