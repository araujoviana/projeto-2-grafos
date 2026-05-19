"""
Tests for the 'Panelinhas em um Grupo Social' project.

Two layers:
  1. Pure-Python unit tests — an independent Bron-Kerbosch implementation
     verifies the expected cliques and influentes for the same 30-vertex graph.
  2. Integration tests — compile the C program with 'make' and assert on stdout.
"""

import os
import subprocess
import sys
import unittest

# ---------------------------------------------------------------------------
# Independent Python implementation
# ---------------------------------------------------------------------------

def _bron_kerbosch(adj, R, P, X, results, min_size):
    if not P and not X:
        if len(R) >= min_size:
            results.append(frozenset(R))
        return
    pivot = max(P | X, key=lambda u: len(adj[u] & P))
    for v in list(P - adj[pivot]):
        _bron_kerbosch(adj, R | {v}, P & adj[v], X & adj[v], results, min_size)
        P = P - {v}
        X = X | {v}


def find_cliques(edges, n, min_size=3):
    """Return all maximal cliques of size >= min_size."""
    adj = {i: set() for i in range(n)}
    for u, v in edges:
        adj[u].add(v)
        adj[v].add(u)
    results = []
    _bron_kerbosch(adj, set(), set(range(n)), set(), results, min_size)
    return results


def find_influentes(cliques, n):
    """Return vertices that are 'influente': appear in 2+ cliques whose
    pairwise intersection is exactly {vertex}."""
    influentes = []
    for v in range(n):
        v_cliques = [c for c in cliques if v in c]
        if len(v_cliques) < 2:
            continue
        for i in range(len(v_cliques)):
            for j in range(i + 1, len(v_cliques)):
                if v_cliques[i] & v_cliques[j] == {v}:
                    influentes.append(v)
                    break
            else:
                continue
            break
    return influentes


# ---------------------------------------------------------------------------
# Graph definition (mirrors main.c exactly)
# ---------------------------------------------------------------------------

N = 30

EDGES = [
    # panelinha 1: Ana, Bruno, Carlos, Daniela {0,1,2,3}
    (0,1),(0,2),(0,3),(1,2),(1,3),(2,3),
    # panelinha 2: Ana, Eduardo, Fernanda {0,4,5}
    (0,4),(0,5),(4,5),
    # panelinha 3: Gabriel, Helena, Igor, Julia {6,7,8,9}
    (6,7),(6,8),(6,9),(7,8),(7,9),(8,9),
    # panelinha 4: Gabriel, Kevin, Laura {6,10,11}
    (6,10),(6,11),(10,11),
    # panelinha 5: Marcos, Natalia, Otavio {12,13,14}
    (12,13),(12,14),(13,14),
    # panelinha 6: Patricia, Rafael, Sabrina {15,16,17}
    (15,16),(15,17),(16,17),
    # panelinha 7: Natalia, Patricia, Thiago {13,15,18}
    (13,15),(13,18),(15,18),
    # panelinha 8: Ursula, Victor, Wanessa {19,20,21}
    (19,20),(19,21),(20,21),
    # panelinha 9: Xavier, Yara, Zeca {22,23,24}
    (22,23),(22,24),(23,24),
    # panelinha 10: Ursula, Xavier, Alice {19,22,25}
    (19,22),(19,25),(22,25),
    # panelinha 11: Alice, Bernardo, Carla {25,26,27}
    (25,26),(25,27),(26,27),
    # panelinha 12: Carla, Diego, Elisa {27,28,29}
    (27,28),(27,29),(28,29),
    # extra edges (no new cliques)
    (2,22),(3,19),(4,20),(5,23),(7,14),(8,16),
    (9,18),(10,26),(11,28),(12,24),(16,21),(17,29),
]

EXPECTED_CLIQUES = [
    frozenset([0,1,2,3]),   # Ana, Bruno, Carlos, Daniela
    frozenset([0,4,5]),     # Ana, Eduardo, Fernanda
    frozenset([6,7,8,9]),   # Gabriel, Helena, Igor, Julia
    frozenset([6,10,11]),   # Gabriel, Kevin, Laura
    frozenset([12,13,14]),  # Marcos, Natalia, Otavio
    frozenset([15,16,17]),  # Patricia, Rafael, Sabrina
    frozenset([13,15,18]),  # Natalia, Patricia, Thiago
    frozenset([19,20,21]),  # Ursula, Victor, Wanessa
    frozenset([22,23,24]),  # Xavier, Yara, Zeca
    frozenset([19,22,25]),  # Ursula, Xavier, Alice
    frozenset([25,26,27]),  # Alice, Bernardo, Carla
    frozenset([27,28,29]),  # Carla, Diego, Elisa
]

# Vertices 0=Ana,6=Gabriel,13=Natalia,15=Patricia,
#          19=Ursula,22=Xavier,25=Alice,27=Carla
EXPECTED_INFLUENTES = {0, 6, 13, 15, 19, 22, 25, 27}

NON_INFLUENTES = set(range(N)) - EXPECTED_INFLUENTES

NAMES = [
    "Ana Clara", "Bruno Henrique", "Carlos Eduardo", "Daniela Ferreira",
    "Eduardo Santos", "Fernanda Lima", "Gabriel Oliveira", "Helena Costa",
    "Igor Matos", "Julia Carvalho", "Kevin Alves", "Laura Rodrigues",
    "Marcos Pereira", "Natalia Souza", "Otavio Mendes", "Patricia Gomes",
    "Rafael Barbosa", "Sabrina Castro", "Thiago Ribeiro", "Ursula Freitas",
    "Victor Moreira", "Wanessa Dias", "Xavier Nunes", "Yara Cavalcanti",
    "Zeca Pinto", "Alice Monteiro", "Bernardo Farias", "Carla Teixeira",
    "Diego Correia", "Elisa Vieira",
]

# ---------------------------------------------------------------------------
# Unit tests — pure Python
# ---------------------------------------------------------------------------

class TestCliqueAlgorithm(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        cls.cliques = find_cliques(EDGES, N)
        cls.influentes = find_influentes(cls.cliques, N)

    def test_total_clique_count(self):
        self.assertEqual(len(self.cliques), 12)

    def test_all_expected_cliques_found(self):
        for c in EXPECTED_CLIQUES:
            self.assertIn(c, self.cliques, f"Clique {c} not found")

    def test_no_unexpected_cliques(self):
        for c in self.cliques:
            self.assertIn(c, EXPECTED_CLIQUES, f"Unexpected clique {c}")

    def test_largest_clique_size(self):
        self.assertEqual(max(len(c) for c in self.cliques), 4)

    def test_two_size4_cliques(self):
        size4 = [c for c in self.cliques if len(c) == 4]
        self.assertEqual(len(size4), 2)
        self.assertIn(frozenset([0,1,2,3]), size4)
        self.assertIn(frozenset([6,7,8,9]), size4)

    def test_influente_count(self):
        self.assertEqual(len(self.influentes), 8)

    def test_expected_influentes_present(self):
        for v in EXPECTED_INFLUENTES:
            self.assertIn(v, self.influentes, f"Vertex {v} ({NAMES[v]}) should be influente")

    def test_non_influentes_absent(self):
        for v in NON_INFLUENTES:
            self.assertNotIn(v, self.influentes, f"Vertex {v} ({NAMES[v]}) should NOT be influente")

    def test_all_vertices_covered(self):
        """Every vertex must belong to at least one clique."""
        covered = set().union(*self.cliques)
        for v in range(N):
            self.assertIn(v, covered, f"Vertex {v} ({NAMES[v]}) has no clique")

    def test_member_query_ana(self):
        ana_cliques = [c for c in self.cliques if 0 in c]
        self.assertEqual(len(ana_cliques), 2)
        self.assertIn(frozenset([0,1,2,3]), ana_cliques)
        self.assertIn(frozenset([0,4,5]),   ana_cliques)

    def test_member_query_gabriel(self):
        cliques = [c for c in self.cliques if 6 in c]
        self.assertEqual(len(cliques), 2)
        self.assertIn(frozenset([6,7,8,9]),  cliques)
        self.assertIn(frozenset([6,10,11]),  cliques)

    def test_member_query_natalia(self):
        cliques = [c for c in self.cliques if 13 in c]
        self.assertEqual(len(cliques), 2)
        self.assertIn(frozenset([12,13,14]), cliques)
        self.assertIn(frozenset([13,15,18]), cliques)

    def test_member_query_thiago_single_clique(self):
        cliques = [c for c in self.cliques if 18 in c]
        self.assertEqual(len(cliques), 1)
        self.assertIn(frozenset([13,15,18]), cliques)

    def test_cliques_are_maximal(self):
        """No clique should be a proper subset of another."""
        for i, a in enumerate(self.cliques):
            for j, b in enumerate(self.cliques):
                if i != j:
                    self.assertFalse(a < b, f"Clique {a} is a proper subset of {b}")

    def test_cliques_are_complete_subgraphs(self):
        """Every reported clique must actually be a clique in the graph."""
        adj = {i: set() for i in range(N)}
        for u, v in EDGES:
            adj[u].add(v)
            adj[v].add(u)
        for clique in self.cliques:
            members = list(clique)
            for i in range(len(members)):
                for j in range(i + 1, len(members)):
                    self.assertIn(
                        members[j], adj[members[i]],
                        f"Missing edge ({members[i]},{members[j]}) in clique {clique}",
                    )


# ---------------------------------------------------------------------------
# Integration tests — compile and run the C program
# ---------------------------------------------------------------------------

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


class TestCProgram(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        build = subprocess.run(
            ["make", "-C", ROOT, "all"],
            capture_output=True, text=True,
        )
        cls.build_ok = build.returncode == 0
        cls.build_err = build.stderr + build.stdout

        cls.output = ""
        if cls.build_ok:
            run = subprocess.run(
                [os.path.join(ROOT, "programa")],
                capture_output=True, text=True, timeout=10,
            )
            cls.output = run.stdout
            cls.exit_code = run.returncode
        else:
            cls.exit_code = -1

    def _skip_if_no_build(self):
        if not self.build_ok:
            self.skipTest(f"Build failed:\n{self.build_err}")

    def test_build_succeeds(self):
        self.assertTrue(self.build_ok, f"Build failed:\n{self.build_err}")

    def test_exits_cleanly(self):
        self._skip_if_no_build()
        self.assertEqual(self.exit_code, 0)

    def test_output_has_network_section(self):
        self._skip_if_no_build()
        self.assertIn("REDE SOCIAL", self.output)

    def test_output_has_panelinhas_section(self):
        self._skip_if_no_build()
        self.assertIn("Panelinhas", self.output)

    def test_output_has_influentes_section(self):
        self._skip_if_no_build()
        self.assertIn("Influentes", self.output)

    def test_output_has_maior_panelinha_section(self):
        self._skip_if_no_build()
        self.assertIn("Maior Panelinha", self.output)

    def test_output_lists_12_panelinhas(self):
        self._skip_if_no_build()
        self.assertIn("12 encontradas", self.output)

    def test_output_largest_clique_size_4(self):
        self._skip_if_no_build()
        self.assertIn("tamanho 4", self.output)

    def test_output_contains_all_participants(self):
        self._skip_if_no_build()
        for name in NAMES:
            self.assertIn(name, self.output, f"Participant '{name}' missing from output")

    def test_output_contains_all_influentes(self):
        self._skip_if_no_build()
        for v in EXPECTED_INFLUENTES:
            self.assertIn(NAMES[v], self.output, f"Influente '{NAMES[v]}' missing from output")


if __name__ == "__main__":
    unittest.main(verbosity=2)
